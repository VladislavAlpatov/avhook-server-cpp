//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include "Base.h"

#define PACKET_SETUSERNAME 0

namespace server::packet
{
    class SetUserName : public Base
    {
    public:
        explicit SetUserName(const nlohmann::json& data);
        std::string execute_payload(int userId) override;
    };
} // packet