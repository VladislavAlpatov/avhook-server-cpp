//
// Created by Vlad on 05.12.2022.
//
#pragma once
#include <string>
#include <vector>
#include "packets/BasePacket.h"
#include "observers/ObservableObject.h"
#include "network/Socket.h"


namespace web
{
	class Server : public ObservableObject
    {
    public:
        static Server *Get();
        Server() = delete;
        void Listen();
        int GetConnectionsCount() const;
    private:
        int m_iConnectedCount = 0;
        bool m_bAllowListen = true;
        Server(const std::string &ip, int port);
        Network::Socket m_sListen;
    };
}