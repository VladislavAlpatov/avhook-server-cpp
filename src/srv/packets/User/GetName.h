//
// Created by vladislav on 07.03.23.
//

#pragma once
#include "UserRelated.h"

namespace web::packet::user
{
    class GetName final : public UserRelated
    {
    public:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
        explicit GetName(const nlohmann::json &data) ;
    };
} // User
