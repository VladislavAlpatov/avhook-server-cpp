//
// Created by nullifiedvlad on 13.12.2022.
//
#pragma once
#include "BasePacket.h"


namespace Web::Packet
    {

        class OnlineUsersICount final : public BasePacket
        {
        public:
            explicit OnlineUsersICount(const nlohmann::json &data);

            nlohmann::json ExecutePayload(int userId) override;


        };

    } // packet