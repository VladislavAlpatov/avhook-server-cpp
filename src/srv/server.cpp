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
#include "PacketFactory.h"
#include <map>
#include "packets/Auth.h"

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

        try
        {
            auto authPacket = recv_packet(clientSocket);

            if (!dynamic_cast<packet::Auth*>(authPacket.get()))
                throw std::runtime_error("Expected Auth packet");

            link_user_with_socket(clientSocket, std::stoi(authPacket->execute_payload(0)));

            printf("[LOG] New client passed auth, client id: \"%d\"\n", get_user_id_by_socket(clientSocket));

            while (true)
                recv_packet(clientSocket)->execute_payload(get_user_id_by_socket(clientSocket));
        }
        catch (const std::exception& ex)
        {
            printf("[LOG] Caught client exception: \"%s\", disconnecting client...\n", ex.what());
            closesocket(clientSocket);
        }
    }

    void Server::recv(SOCKET soc, void *pBuff, int buffSize)
    {
        int wholeRecievedBytes = 0;

        while (wholeRecievedBytes < buffSize)
        {
            auto recievedBytes = ::recv(soc, (char *) pBuff, buffSize - wholeRecievedBytes, NULL);
            if (recievedBytes <= 0)
                throw server::exception::RecvFailed();
            wholeRecievedBytes += recievedBytes;
        }

    }

    int Server::recv_packet_size(SOCKET soc)
    {
        int packetSize = 0;
        recv(soc, &packetSize, sizeof(packetSize));

        return packetSize;
    }


    std::shared_ptr<packet::Base> Server::recv_packet(SOCKET soc)
    {
        const auto size = recv_packet_size(soc);

        const auto data = std::unique_ptr<char>(new char[size+1]);
        ZeroMemory(data.get(), size+1);

        recv(soc, data.get(), size);
        return PacketFactory::create(nlohmann::json::parse(data.get()));
    }

    void Server::link_user_with_socket(SOCKET soc, int id)
    {
        std::lock_guard guard(m_LinkedMapMutex);

        m_mLinkedUsers[soc] = id;
    }

    void Server::unlink_user_with_socket(SOCKET soc)
    {
        std::lock_guard guard(m_LinkedMapMutex);
        m_mLinkedUsers.erase(soc);
    }

    int Server::get_user_id_by_socket(SOCKET soc)
    {
        std::lock_guard guard(m_LinkedMapMutex);
        if (!m_mLinkedUsers.contains(soc))
            throw exception::ClientNotRegistered();

        return m_mLinkedUsers[soc];
    }
}