//
// Created by Vladislav on 28.03.2023.
//

#pragma once
#include "UserRelated.h"

namespace Web::Packet::User
{
    class GetConfigs : public UserRelated
    {
    public:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };

}
