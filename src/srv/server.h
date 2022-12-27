//
// Created by Vlad on 05.12.2022.
//
#pragma once
#include <WinSock2.h>
#include <string>
#include <vector>
#include "packets/Base.h"

#define INVALID_USER_ID (-1)

namespace Web
{
    class Server
    {
    public:
        static Server *Get();
        Server() = delete;
        void Listen();

    private:
        bool m_bAllowListen = true;
        Server(const std::string &ip, int port);
        SOCKET m_sListen;
    };
}