//
// Created by nullifiedvlad on 13.12.2022.
//
#pragma once
#include "Base.h"

#define PACKET_GETUSERINFO 4

namespace server::packet
{
    class GetUserInfo final : public Base
    {
    public:
        explicit GetUserInfo(const nlohmann::json &data);

        std::string execute_payload(int userId) override;
    };
} // packet