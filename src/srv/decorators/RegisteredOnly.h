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
        explicit RegisteredOnly(const std::shared_ptr<BasePacket> &pPacket);

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };
} // Decorator