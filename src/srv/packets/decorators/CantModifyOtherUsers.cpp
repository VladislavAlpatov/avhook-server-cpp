//
// Created by vladislav on 10.03.23.
//

#include "CantModifyOtherUsers.h"
#include "../UserRelated/UserRelated.h"
#include "../Misc/Auth.h"
namespace Web::Packet::Decorator
{


    nlohmann::json CantModifyOtherUsers::ExecutePayload(ClientHandle &clientHandle)
    {
        // auto ptr = GetOriginalPacket<Packet::Auth>();
        return m_pDecoratedPacket->ExecutePayload(clientHandle);
    }
}