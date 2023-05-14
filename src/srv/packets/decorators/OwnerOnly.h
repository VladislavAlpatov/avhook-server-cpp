//
// Created by vladislav on 10.03.23.
//

#pragma once
#include "BaseDecorator.h"

namespace dbapi
{
    class User;
}

namespace web::packet::decorator
{
    class OwnerOnly final : public BaseDecorator
    {
    public:
        OwnerOnly() = default;

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };

}
