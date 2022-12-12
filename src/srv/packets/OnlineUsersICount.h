//
// Created by nullifiedvlad on 13.12.2022.
//
#pragma once
#include "Base.h"

#define PACKET_ONLINEUSERSCOUNT 3

namespace server::packet
    {

        class OnlineUsersICount final : public Base
        {
        public:
            explicit OnlineUsersICount(const nlohmann::json &data);

            std::string execute_payload(int userId) override;


        };

    } // packet