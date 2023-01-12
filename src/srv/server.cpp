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


namespace Web
{
    Server::Server(const std::string &ip, const int port)
    {
        m_sListen.Bind(ip, port);
    }

    Server *Server::Get()
    {
        static std::unique_ptr<Server> pServer;
        if (!pServer)
            pServer = std::unique_ptr<Server>(new Server("0.0.0.0", 7777));

        return pServer.get();
    }

    void Server::Listen()
    {
		NotifyObserver<Observers::OnServerStartup>();


        while (m_bAllowListen)
        {

            auto connectionSocket = m_sListen.Listen();

            NotifyObserver<Observers::OnUserConnected>();
            m_iConnectedCount++;

			std::thread([this, connectionSocket]
			{
				auto clientHandle = ClientHandle(connectionSocket);

				clientHandle.AddObserver(new Observers::OnUserAuth());
				clientHandle.AddObserver(new Observers::OnPacket());

                try
                {
                    clientHandle.Listen();
                }
                catch (...)
                {
                    NotifyObserver<Observers::OnUserDisconnected>();
                    m_iConnectedCount--;
                }
			}).detach();

        }
    }

    int Server::GetConnectionsCount() const
    {
        return m_iConnectedCount;
    }
}