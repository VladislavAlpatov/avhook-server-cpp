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
#include <map>

#define INVALID_USER_ID -1

namespace server
{
    class Server
    {
    public:
        static Server *get();
        Server() = delete;
        void listen();

    private:
        static std::shared_ptr<packet::Base> recv_packet(SOCKET soc);
        static void client_handler(SOCKET clientSocket);

        bool m_bAllowListen = true;

        Server(const std::string &ip, int port);

        SOCKET m_sListen;

        static void recv(SOCKET soc, void *pBuff, int buffSize);
        static void send_string(SOCKET soc, const std::string& str);
        static int recv_packet_size(SOCKET soc);


    };
}