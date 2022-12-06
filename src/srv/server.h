//
// Created by Vlad on 05.12.2022.
//
#pragma once
#include <WinSock2.h>
#include <string>
#include <vector>
#include <mutex>


namespace server
{
    class Server
    {
    public:
        static Server *get();

        void listen();

    private:
        std::vector<SOCKET> m_vActiveConnections;

        void client_handler(SOCKET clientSocket);

        bool m_bAllowListen;

        Server(const std::string &ip, int port);

        SOCKET m_sListen;

        static void recv(SOCKET soc, void *pBuff, int buffSize);
        static int recv_packet_size(SOCKET soc);

    };
}