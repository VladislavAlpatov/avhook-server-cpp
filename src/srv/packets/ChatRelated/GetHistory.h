//
// Created by Vladislav on 3/19/2023.
//

#pragma once
#include "ChatRelated.h"


namespace Web::Packet::Chat
{
    class GetHistory final : public ChatRelated
    {
    public:
        explicit GetHistory(const nlohmann::json &data);

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };

}

