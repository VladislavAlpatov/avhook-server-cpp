//
// Created by Vlad on 27.12.2022.
//
#include "ClientHandle.h"
#include <thread>
#include "../network/network.h"
#include "../packets/Auth.h"
#include "../packets/exceptions.h"
#include "../../lib/sqlite/connection.h"
#include <fmt/format.h>

#define INVALID_USER_ID (-1)

int AuthClient(SOCKET clientSocket)
{
	while (true)
	{
		try
		{
			auto pAuthPacket = Web::Network::RecvPacket(clientSocket);

			if (!dynamic_cast<Web::Packet::Auth*>(pAuthPacket.get()))
				throw Web::Packet::Exception::ExceptedAutPacket();

			int iUserId = pAuthPacket->ExecutePayload(NULL)["user_id"].get<int>();

			sql::Connection::get()->query(fmt::format("UPDATE `users` SET `is_online` = TRUE WHERE `id` = {}", iUserId));

			nlohmann::json jsn;
			jsn["success"] = true;
			Web::Network::SendJson(clientSocket, jsn);

			return iUserId;
		}
		catch(const Web::Packet::Exception::BasePacketException& ex)
		{
			nlohmann::json jsn;
			jsn["success"] = false;
			jsn["error_code"] = ex.what();
			Web::Network::SendJson(clientSocket, jsn);
		}

	}

}

void OnPacket(int iUserId,SOCKET clientSocket, const std::shared_ptr<Web::Packet::Base>& pPacket)
{
	auto jsn = pPacket->ExecutePayload(iUserId);
	jsn["success"] = true;

	Web::Network::SendJson(clientSocket,jsn);

}
void ClientHandle(SOCKET clientSocket)
{
	int iUserId = INVALID_USER_ID;

	try
	{
		iUserId = AuthClient(clientSocket);

		try
		{
			OnPacket(iUserId, clientSocket, Web::Network::RecvPacket(clientSocket));
		}
		catch (const Web::Packet::Exception::BasePacketException& ex)
		{
			nlohmann::json jsn;

			jsn["success"]    = false;
			jsn["error_code"] = ex.what();

			Web::Network::SendJson(clientSocket, jsn);
		}

	}
	catch (const std::exception& ex)
	{
		printf("[LOG] Caught fatal client exception: \"%s\", disconnecting client...\n", ex.what());
		closesocket(clientSocket);

		if (INVALID_USER_ID != iUserId)
			sql::Connection::get()->query(fmt::format("UPDATE `users` SET `is_online` = FALSE WHERE `id` = {}", iUserId));
	}
}

void Web::ClientHandle::CreateNewThreadHandle(SOCKET clientSocket)
{
	std::thread([clientSocket]
	{
		::ClientHandle(clientSocket);
	}
	).detach();
}

