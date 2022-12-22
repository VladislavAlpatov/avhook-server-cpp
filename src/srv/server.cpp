//
// Created by Vlad on 05.12.2022.
//
#include "server.h"
#include <stdexcept>
#include <ws2tcpip.h>
#include <memory>
#include <thread>
#include "../consts.h"
#include "exceptions.h"
#include <fmt/format.h>

#include "PacketFactory.h"
#include "packets/Auth.h"
#include "../lib/sqlite/connection.h"
#include "../lib/nnl/nnl.h"
#include "packets/exceptions.h"


namespace server
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
            throw std::runtime_error("Failed to create listen socket");
        bind(m_sListen, (SOCKADDR *) &addr, sizeof(addr));
    }

    Server *Server::get()
    {
        static std::unique_ptr<Server> pServer;
        if (!pServer)
            pServer = std::unique_ptr<Server>(new Server("127.0.0.1", 7777));

        return pServer.get();
    }

    void Server::listen()
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

            std::thread([this, connectionSocket]
                        { client_handler(connectionSocket); }).detach();
        }
    }

    void Server::client_handler(SOCKET clientSocket)
    {
        printf("[LOG] Connected new user\n");
        int iUserId = INVALID_USER_ID;
        try
        {
            iUserId = auth_client(clientSocket);

            printf("[LOG] New client passed auth, client id: \"%d\"\n", iUserId);

            while (true)
            {
                auto res = recv_packet(clientSocket)->execute_payload(iUserId);

                if (res.empty()) continue;

                nnl::send_string(clientSocket, res);
            }
        }
        catch (const std::exception& ex)
        {
            printf("[LOG] Caught client exception: \"%s\", disconnecting client...\n", ex.what());
            closesocket(clientSocket);

            if (iUserId != INVALID_USER_ID)
                sql::Connection::get()->query(fmt::format("UPDATE `users` SET `is_online` = FALSE WHERE `id` = {}", iUserId));
        }
    }

    std::shared_ptr<packet::Base> Server::recv_packet(SOCKET soc)
    {
        return PacketFactory::create(nnl::recv_json(soc));
    }
    int  Server::auth_client(SOCKET clientSocket)
    {
        while (true)
        {
            try
            {
                auto pAuthPacket = recv_packet(clientSocket);
            
                if (!dynamic_cast<packet::Auth*>(pAuthPacket.get()))
                {
                    nnl::send_string(clientSocket, "Acces denied");
                    continue;
                }
                int iUserId = std::stoi(pAuthPacket->execute_payload(NULL));

                sql::Connection::get()->query(fmt::format("UPDATE `users` SET `is_online` = TRUE WHERE `id` = {}", iUserId));

                return iUserId;
            }
            catch(const packet::exception::AuthFailedWrongPassword& ex)
            {
                nnl::send_string(clientSocket, ex.what());
            }
            
        }
        
    }
}