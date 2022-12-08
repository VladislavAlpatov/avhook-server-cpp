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

namespace server
{
    class Server
    {
    public:
        static Server *get();
        Server() = delete;
        void listen();

    private:
        void link_user_with_socket(SOCKET soc, int id);
        void unlink_user_with_socket(SOCKET soc);
        int get_user_id_by_socket(SOCKET soc);
        std::shared_ptr<packet::Base> recv_packet(SOCKET soc);
        void client_handler(SOCKET clientSocket);
        std::map<SOCKET, int> m_mLinkedUsers;

        bool m_bAllowListen = true;

        Server(const std::string &ip, int port);
        std::mutex m_LinkedMapMutex;

        SOCKET m_sListen;

        static void recv(SOCKET soc, void *pBuff, int buffSize);
        static int recv_packet_size(SOCKET soc);


    };
}