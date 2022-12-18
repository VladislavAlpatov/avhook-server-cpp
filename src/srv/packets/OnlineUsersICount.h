//
// Created by nullifiedvlad on 13.12.2022.
//
#pragma once
#include "Base.h"


namespace server::packet
    {

        class OnlineUsersICount final : public Base
        {
        public:
            explicit OnlineUsersICount(const nlohmann::json &data);

            std::string execute_payload(int userId) override;


        };

    } // packet