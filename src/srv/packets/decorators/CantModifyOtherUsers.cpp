//
// Created by vladislav on 10.03.23.
//

#include "CantModifyOtherUsers.h"
#include "../UserRelated/UserRelated.h"
namespace Web::Packet::Decorator
{


    nlohmann::json CantModifyOtherUsers::ExecutePayload(ClientHandle &clientHandle)
    {
        auto pPacket = GetOriginalPacket<Packet::User::UserRelated>();

        if (pPacket->m_pUserFromPacket != clientHandle.m_dbUser and !clientHandle.m_dbUser.HasRightsOf(DBAPI::User::Rights::Developer))
            throw std::runtime_error("You cant modify data of other users");


        return m_pDecoratedPacket->ExecutePayload(clientHandle);
    }
}