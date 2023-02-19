//
// Created by Vlad on 19.02.2023.
//

#include "PremiumOnly.h"


namespace Web::Packet::Decorator
{

    nlohmann::json PremiumOnly::ExecutePayload(ClientHandle &clientHandle)
    {
        return RegisteredOnly::ExecutePayload(clientHandle);
    }

}