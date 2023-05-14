//
// Created by Vladislav on 3/18/2023.
//

#pragma once
#include "ChatRelated.h"


namespace web::packet::chat
{
    class GetName final : public ChatRelated
    {
    public:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;

        explicit GetName(const nlohmann::json &data);

    };

}
