//
// Created by Vladislav on 3/18/2023.
//
#pragma once
#include "BaseDecorator.h"


namespace Web::Packet::Decorator
{
    class AdminOnly : public BaseDecorator
    {
    public:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };

}