//
// Created by alpat on 20.01.2023.
//

#pragma once
#include "BaseDecorator.h"
#include "../ClientHandle/ClientHandle.h"


namespace Web::Packet::Decorator
{
    class RegisteredOnly : public BaseDecorator
    {
    public:
        explicit RegisteredOnly(std::unique_ptr<BasePacket>& pPacket);
        RegisteredOnly() =  default;
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };
} // Decorator