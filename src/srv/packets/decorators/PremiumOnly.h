//
// Created by Vlad on 19.02.2023.
//
#pragma once
#include "RegisteredOnly.h"


namespace web::packet::decorator
{
    class PremiumOnly : public RegisteredOnly
    {
    public:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };
} // decorator

