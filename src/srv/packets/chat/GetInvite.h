//
// Created by Vladislav on 3/19/2023.
//

#pragma once
#include "ChatRelated.h"


namespace web::packet::chat
{
    class GetInvite final : public ChatRelated
    {
    public:
        explicit GetInvite(const nlohmann::json &data);

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };

}