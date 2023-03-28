//
// Created by vladislav on 10.03.23.
//

#pragma once
#include "BaseDecorator.h"

namespace DBAPI
{
    class User;
}

namespace Web::Packet::Decorator
{
    class OwnerOnly final : public BaseDecorator
    {
    public:
        OwnerOnly() = default;

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };

}
