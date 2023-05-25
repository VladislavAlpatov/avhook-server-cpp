//
// Created by vlad on 25.05.23.
//

#include "GetProduct.h"

namespace web::packet::subscription
{

    nlohmann::json GetProduct::ExecutePayload(ClientHandle &clientHandle)
    {
        return {{"product_id", m_SubFromPacket.GetUserId()}};
    }

    GetProduct::GetProduct(const nlohmann::json &data) : SubscriptionRelated(data)
    {}
}