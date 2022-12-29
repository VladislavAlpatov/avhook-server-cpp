//
// Created by Vlad on 05.12.2022.
//
#include "server.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


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
        sockaddr_in addr{};

        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.s_addr);
        addr.sin_port = htons(port);
        addr.sin_family = AF_INET;

        m_sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (!m_sListen)
            throw std::runtime_error("Failed to Create Listen socket");
        bind(m_sListen, (sockaddr*)&addr, sizeof(addr));
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
            ::listen(m_sListen, SOMAXCONN);

            auto connectionSocket = accept(m_sListen, NULL, NULL);

            if (!connectionSocket) continue;


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