//
// Created by Vlad on 05.12.2022.
//
#include "server.h"

#include <stdexcept>
#include <thread>

#include "ClientHandle/ClientHandle.h"

#include "observers/OnUserConnected.h"
#include "observers/OnServerStartup.h"
#include "observers/OnUserDisconnected.h"
#include "observers/OnUserAuth.h"
#include "observers/OnPacket.h"

#include "DataBaseAPI/DataBase.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>



namespace web
{
    Server::Server(const std::string &ip, const int port)
    {
        m_sListen = network::Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        m_sListen.SetOption(IPPROTO_TCP, TCP_NODELAY, 1);
        m_sListen.Bind(ip, port);

        // Initialize database by calling Get function
        // at first time
        dbapi::DataBase::Get();
    }

    Server *Server::Get()
    {
        static std::unique_ptr<Server> pServer;
        if (!pServer)
#ifndef _DEBUG
            pServer = std::unique_ptr<Server>(new Server("0.0.0.0",std::stoi(std::getenv("PORT"))));
#else
        pServer = std::unique_ptr<Server>(new Server("0.0.0.0",7777));
#endif

        return pServer.get();
    }

    void Server::Listen()
    {
		NotifyObserver<observers::OnServerStartup>();


        while (m_bAllowListen)
        {

            auto connectionSocket = m_sListen.Listen();
            connectionSocket.SetOption(IPPROTO_TCP, TCP_NODELAY, 1);

            NotifyObserver<observers::OnUserConnected>();
            m_iConnectedCount++;

			std::thread([this](const network::Socket& soc)
			{
				auto clientHandle = ClientHandle(soc);

#ifdef _DEBUG
				clientHandle.AddObserver(new observers::OnUserAuth());
				clientHandle.AddObserver(new observers::OnPacket());
#endif

                clientHandle.Listen();
                NotifyObserver<observers::OnUserDisconnected>();
                m_iConnectedCount--;

			}, std::move(connectionSocket)).detach();

        }
    }

    int Server::GetConnectionsCount() const
    {
        return m_iConnectedCount;
    }
}