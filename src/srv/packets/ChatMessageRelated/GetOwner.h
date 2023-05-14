//
// Created by Vladislav on 3/20/2023.
//

#pragma once
#include "ChatMessageRelated.h"
namespace web::packet::message
{
    class GetOwner final : public ChatMessageRelated
    {
    public:
        explicit GetOwner(const nlohmann::json &data);

    private:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };

}
