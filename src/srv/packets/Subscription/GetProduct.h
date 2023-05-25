//
// Created by vlad on 25.05.23.
//
#pragma once
#include "SubscriptionRelated.h"

namespace web::packet::subscription
{
    class GetProduct : public SubscriptionRelated
    {
    public:
        explicit GetProduct(const nlohmann::json &data);

    public:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };
}
