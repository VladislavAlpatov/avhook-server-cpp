//
// Created by Vlad on 27.12.2022.
//
#include "ClientHandle.h"
#include "../network/network.h"
#include "../packets/Auth.h"
#include "../packets/exceptions.h"
#include "../../lib/sqlite/connection.h"

#include "../observers/OnUserConnected.h"
#include "../observers/OnUserDisconnected.h"
#include "../observers/OnUserAuth.h"
#include "../observers/OnPacket.h"


#include <fmt/format.h>

#define INVALID_USER_ID (-1)

void Web::ClientHandle::Listen()
{
	NotifyObserver<Observers::OnUserConnected>();

	try
	{
		AuthClient();
		while (true)
		{
			try
			{
				OnPacket(Web::Network::RecvPacket(m_clientSocket));
			}
			catch (const Web::Packet::Exception::BasePacketException& ex)
			{
				nlohmann::json jsn;

				jsn["success"]    = false;
				jsn["error_code"] = ex.what();

				Web::Network::SendJson(m_clientSocket, jsn);
			}
		}

	}
	catch (const std::exception& ex)
	{

		if (INVALID_USER_ID != m_iUserIdInDataBase)
			sql::Connection::Get()->Query(
					fmt::format("UPDATE `users` SET `is_online` = FALSE WHERE `id` = {}", m_iUserIdInDataBase));

		NotifyObserver<Observers::OnUserDisconnected>();
	}
}

Web::ClientHandle::~ClientHandle()
{
	closesocket(m_clientSocket);
}

void Web::ClientHandle::AuthClient()
{
	while (true)
	{
		try
		{
			auto pAuthPacket = Web::Network::RecvPacket(m_clientSocket);

			if (!dynamic_cast<Web::Packet::Auth*>(pAuthPacket.get()))
				throw Web::Packet::Exception::ExceptedAutPacket();

			m_iUserIdInDataBase = pAuthPacket->ExecutePayload(NULL)["user_id"].get<int>();

			sql::Connection::Get()->Query(
					fmt::format("UPDATE `users` SET `is_online` = TRUE WHERE `id` = {}", m_iUserIdInDataBase));

			nlohmann::json jsn;
			jsn["success"] = true;
			NotifyObserver<Observers::OnUserAuth>();
			Web::Network::SendJson(m_clientSocket, jsn);

			return;
		}
		catch(const Web::Packet::Exception::BasePacketException& ex)
		{
			nlohmann::json jsn;
			jsn["success"] = false;
			jsn["error_code"] = ex.what();
			Web::Network::SendJson(m_clientSocket, jsn);
		}

	}
}

void Web::ClientHandle::OnPacket(const std::shared_ptr<Web::Packet::Base>& pPacket) const
{
	NotifyObserver<Observers::OnPacket>();
	auto jsn = pPacket->ExecutePayload(m_iUserIdInDataBase);
	jsn["success"] = true;

	Web::Network::SendJson(m_clientSocket,jsn);
}

Web::ClientHandle::ClientHandle(SOCKET soc)
{
	m_clientSocket = soc;
}
