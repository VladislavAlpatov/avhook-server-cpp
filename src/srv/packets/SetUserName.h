//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include "Base.h"
#include "../../lib/sqlite/connection.h"

#define PACKET_SETUSERNAME 0

namespace server::packet
{
    class SetUserName : public Base
    {
    public:
        explicit SetUserName(const nlohmann::json& data, sql::Connection* pConn);
        sql::Connection* m_pConn;
        std::string execute_payload() override;

    public:
    };
} // packet