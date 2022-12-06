//
// Created by Vlad on 05.12.2022.
//
#pragma once
#include <WinSock2.h>
#include <string>
#include <vector>
#include <mutex>
#include "../lib/sqlite/connection.h"
#include "packets/Base.h"

namespace server
{
    class Server
    {
    public:
        static Server *get();
        Server() = delete;
        void listen();

    private:
        bool auth_client(SOCKET clientSocket);
        std::vector<SOCKET> m_vActiveConnections;
        std::shared_ptr<packet::Base> recv_packet(SOCKET soc);
        void client_handler(SOCKET clientSocket);
        sql::Connection m_dataBaseConn;

        bool m_bAllowListen = true;

        Server(const std::string &ip, int port);

        SOCKET m_sListen;

        static void recv(SOCKET soc, void *pBuff, int buffSize);
        static int recv_packet_size(SOCKET soc);


    };
}