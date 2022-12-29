//
// Created by Vlad on 05.12.2022.
//
#pragma once
#include <string>
#include <vector>
#include "packets/Base.h"
#include "ObservableObject.h"

namespace Web
{
	class Server : public ObservableObject
    {
    public:
        static Server *Get();
        Server() = delete;
        void Listen();

    private:
        bool m_bAllowListen = true;
        Server(const std::string &ip, int port);
        int m_sListen;
    };
}