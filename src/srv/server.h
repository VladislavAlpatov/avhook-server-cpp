//
// Created by Vlad on 05.12.2022.
//
#pragma once
#include <WinSock2.h>
#include <string>
#include <vector>
#include "packets/Base.h"

#define INVALID_USER_ID -1

namespace Web
{
    class Server
    {
    public:
        static Server *get();
        Server() = delete;
        void listen();

    private:
        static std::shared_ptr<packet::Base> recv_packet(SOCKET soc);
        void client_handler(SOCKET clientSocket);
        int  auth_client(SOCKET clientSocket);
        bool m_bAllowListen = true;

        Server(const std::string &ip, int port);

        SOCKET m_sListen;
    };
}