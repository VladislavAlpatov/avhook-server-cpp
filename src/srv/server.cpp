//
// Created by Vlad on 05.12.2022.
//
#include "server.h"

#include <stdexcept>
#include <thread>

#include "../lib/sqlite/connection.h"
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
        // Reset `is_online` flag for all users
		sql::Connection::Get()->Query("UPDATE `users` SET `is_online` = FALSE");

		NotifyObserver<Observers::OnServerStartup>();


        while (m_bAllowListen)
        {

            auto connectionSocket = m_sListen.Listen();

			std::thread([connectionSocket]
			{
				auto clientHandle = ClientHandle(connectionSocket);

				clientHandle.AddObserver(new Observers::OnUserConnected());
				clientHandle.AddObserver(new Observers::OnUserDisconnected());
				clientHandle.AddObserver(new Observers::OnUserAuth());
				clientHandle.AddObserver(new Observers::OnPacket());


				clientHandle.Listen();

			}).detach();

			NotifyObserver<Observers::OnUserConnected>();

        }
    }
}