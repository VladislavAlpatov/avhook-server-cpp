//
// Created by Vladislav on 28.03.2023.
//

#pragma once
#include "UserRelated.h"

namespace web::packet::user
{
    class GetConfigs : public UserRelated
    {
    public:
        explicit GetConfigs(const nlohmann::json &data);

    public:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };

}
