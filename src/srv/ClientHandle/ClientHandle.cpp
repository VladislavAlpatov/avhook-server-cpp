//
// Created by Vlad on 27.12.2022.
//
#include "ClientHandle.h"

#include <utility>
#include "../observers/OnPacket.h"
#include "../network/exceptions.h"

#include <fmt/format.h>
#include "../factories/PacketFactory.h"

void Web::ClientHandle::Listen()
{
    while (true)
    {
        try
        {
            OnPacket(RecvPacket());
        }
        catch (const Network::Exception::RecvFailed& ex)
        {
            return;
        }
        catch (const std::exception& ex)
        {
            nlohmann::json jsn;

            jsn["success"]    = false;
            jsn["error_code"] = ex.what();

            SendJson(jsn);
        }
    }
}

Web::ClientHandle::~ClientHandle()
{
    m_clientSocket.Close();
}

void Web::ClientHandle::OnPacket(const std::unique_ptr<IPayloadExecutable>& pPacket)
{
	NotifyObserver<Observers::OnPacket>();
	auto jsn = pPacket->ExecutePayload(*this);
	jsn["success"] = true;

    SendJson(jsn);
}

Web::ClientHandle::ClientHandle(Network::Socket soc)
{
	m_clientSocket = soc;
}

void Web::ClientHandle::SendString(const std::string& str)
{
	m_clientSocket.SendBytes(str.data(), str.size());
}

void Web::ClientHandle::SendJson(const nlohmann::json& jsn)
{
	SendString(jsn.dump());
}

std::string Web::ClientHandle::RecvString()
{
	auto data = m_clientSocket.RecvBytes();
	data.push_back('\0');
	return (char*)data.data();
}

nlohmann::json Web::ClientHandle::RecvJson()
{
	return nlohmann::json::parse(RecvString());
}

std::unique_ptr<Web::IPayloadExecutable> Web::ClientHandle::RecvPacket()
{
	return PacketFactory::Create(RecvJson());
}

