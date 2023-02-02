//
// Created by Vlad on 27.12.2022.
//
#include "ClientHandle.h"
#include "../packets/exceptions.h"
#include "../observers/OnPacket.h"


#include <fmt/format.h>


void Web::ClientHandle::Listen()
{
    while (true)
    {
        try
        {
            OnPacket(m_clientSocket.RecvPacket());
        }
        catch (const Packet::Exception::BasePacketException& ex)
        {
            nlohmann::json jsn;

            jsn["success"]    = false;
            jsn["error_code"] = ex.what();

            m_clientSocket.SendJson(jsn);
        }
    }
}

Web::ClientHandle::~ClientHandle()
{

}

void Web::ClientHandle::OnPacket(const std::unique_ptr<Web::Packet::BasePacket>& pPacket)
{
	NotifyObserver<Observers::OnPacket>();
	auto jsn = pPacket->ExecutePayload(*this);
	jsn["success"] = true;

    m_clientSocket.SendJson(jsn);
}

Web::ClientHandle::ClientHandle(const Network::Socket& soc)
{
	m_clientSocket = soc;
}
