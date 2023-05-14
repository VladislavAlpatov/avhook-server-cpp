//
// Created by Vladislav on 3/19/2023.
//

#pragma once

#include "ChatMessageRelated.h"

namespace web::packet::message
{
    class GetText final : public ChatMessageRelated
    {
    public:
        explicit GetText(const nlohmann::json &data);

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };

}
