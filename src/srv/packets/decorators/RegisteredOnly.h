//
// Created by alpat on 20.01.2023.
//

#pragma once
#include "BaseDecorator.h"
#include "../../ClientHandle/ClientHandle.h"


namespace web::packet::decorator
{
    class RegisteredOnly : public BaseDecorator
    {
    public:
        explicit RegisteredOnly(std::unique_ptr<IPayloadExecutable>& pPacket);
        RegisteredOnly() =  default;
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };
} // decorator