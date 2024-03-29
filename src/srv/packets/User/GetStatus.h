//
// Created by vladislav on 07.03.23.
//
#pragma once
#include "UserRelated.h"


namespace web::packet::user
{
    class GetStatus final : public UserRelated
    {
    public:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
        explicit GetStatus(const nlohmann::json &data);
    };
} // User