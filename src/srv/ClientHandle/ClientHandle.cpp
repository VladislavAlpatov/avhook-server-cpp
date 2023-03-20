//
// Created by Vlad on 27.12.2022.
//
#include "ClientHandle.h"

#include <utility>
#include "../observers/OnPacket.h"
#include "../network/exceptions.h"

#include <fmt/format.h>


void Web::ClientHandle::Listen()
{
    while (true)
    {
        try
        {
            OnPacket(m_clientSocket.RecvPacket());
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

            m_clientSocket.SendJson(jsn);
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

    m_clientSocket.SendJson(jsn);
}

Web::ClientHandle::ClientHandle(Network::Socket soc)
{
	m_clientSocket = soc;
}
