//
// Created by nullifiedvlad on 07.12.2022.
//
#pragma once
#include "packets/Base.h"
#include <memory>
#include "../lib/sqlite/connection.h"
namespace server
{

    class PacketFactory
    {
    public:
        static std::shared_ptr<packet::Base> create(const nlohmann::json& data, sql::Connection* pConn);
    };

} // server