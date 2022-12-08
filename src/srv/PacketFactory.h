//
// Created by nullifiedvlad on 07.12.2022.
//
#pragma once
#include "packets/Base.h"
#include <memory>
#include <WinSock2.h>
namespace server
{
    class PacketFactory final
    {
        friend class Server;
    private:
        static std::shared_ptr<packet::Base> create(const nlohmann::json& data);
    };

} // server