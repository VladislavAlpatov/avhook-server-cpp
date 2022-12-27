//
// Created by Vlad on 05.12.2022.
//
#include "server.h"
#include <stdexcept>
#include <ws2tcpip.h>
#include "../lib/sqlite/connection.h"
#include "ClientHandle/ClientHandle.h"


namespace Web
{
    Server::Server(const std::string &ip, const int port)
    {
        WSADATA data;
        if (WSAStartup(MAKEWORD(2, 2), &data))
            throw std::runtime_error("Failed to initialize WinSock 2.2");

        SOCKADDR_IN addr;
        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.S_un.S_addr);
        addr.sin_port = htons(port);
        addr.sin_family = AF_INET;

        m_sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (!m_sListen)
            throw std::runtime_error("Failed to Create Listen socket");
        bind(m_sListen, (SOCKADDR *) &addr, sizeof(addr));
    }

    Server *Server::Get()
    {
        static std::unique_ptr<Server> pServer;
        if (!pServer)
            pServer = std::unique_ptr<Server>(new Server("127.0.0.1", 7777));

        return pServer.get();
    }

    void Server::Listen()
    {
        // Reset `is_online` flag for all users
        sql::Connection::get()->query("UPDATE `users` SET `is_online` = FALSE");

        printf("[LOG] Server is online, listening...\n");


        while (m_bAllowListen)
        {
            ::listen(m_sListen, SOMAXCONN);
            sockaddr_in addr{};
            int size = sizeof(addr);

            auto connectionSocket = accept(m_sListen, (sockaddr *) &addr, &size);

            if (!connectionSocket) continue;
				ClientHandle::CreateNewThreadHandle(connectionSocket);


        }
    }
}