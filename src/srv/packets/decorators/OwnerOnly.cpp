//
// Created by vladislav on 10.03.23.
//

#include "OwnerOnly.h"
#include "../interfaces/IUserAccessible.h"
namespace web::packet::decorator
{


    nlohmann::json OwnerOnly::ExecutePayload(ClientHandle &clientHandle)
    {
        auto pPacket = GetOriginalPacket<IUserAccessible>();

        if (pPacket->GetUser() != clientHandle.m_dbUser and !clientHandle.m_dbUser.HasRightsOf(dbapi::User::Rights::Developer))
            throw std::runtime_error("You cant modify data of other users");


        return m_pDecoratedPacket->ExecutePayload(clientHandle);
    }
}