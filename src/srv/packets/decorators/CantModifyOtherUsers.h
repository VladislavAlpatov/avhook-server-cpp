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
    class CantModifyOtherUsers final : public BaseDecorator
    {
    public:
        CantModifyOtherUsers() = default;

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    private:
        DBAPI::User m_userFromPacket;
    };

}
