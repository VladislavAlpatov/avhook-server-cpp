//
// Created by Vladislav on 3/18/2023.
//

#include "AdminOnly.h"

namespace Web::Packet::Decorator
{
    nlohmann::json AdminOnly::ExecutePayload(Web::ClientHandle &clientHandle)
    {
        using DBAPI::User;


        if (!clientHandle.m_dbUser.HasRightsOf(User::Rights::Admin))
            throw std::runtime_error("You cant access to this packet, its has Admin permissions");

        return m_pDecoratedPacket->ExecutePayload(clientHandle);
    }

}
