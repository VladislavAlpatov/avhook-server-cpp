//
// Created by Vladislav on 3/18/2023.
//

#include "AdminOnly.h"

namespace web::packet::decorator
{
    nlohmann::json AdminOnly::ExecutePayload(web::ClientHandle &clientHandle)
    {
        using dbapi::User;


        if (!clientHandle.m_dbUser.HasRightsOf(User::Rights::Admin))
            throw std::runtime_error("You cant access to this packet, its has Admin permissions");

        return m_pDecoratedPacket->ExecutePayload(clientHandle);
    }

}
