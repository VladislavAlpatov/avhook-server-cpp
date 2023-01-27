//
// Created by alpat on 20.01.2023.
//

#include "RegisteredOnly.h"
#include "exceptions.h"

namespace Web::Packet::Decorator
{

    nlohmann::json RegisteredOnly::ExecutePayload(ClientHandle& clientHandle)
    {
        if (clientHandle.m_iUserIdInDataBase == INVALID_USER_ID)
            throw Exception::UserNotRegistered();

        return  m_pDecoratedPacket->ExecutePayload(clientHandle);
    }

    RegisteredOnly::RegisteredOnly(const std::shared_ptr<BasePacket> &pPacket) : BaseDecorator(pPacket)
    {

    }
} // Decorator