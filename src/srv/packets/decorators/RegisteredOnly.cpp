//
// Created by alpat on 20.01.2023.
//

#include "RegisteredOnly.h"
#include "exceptions.h"

namespace Web::Packet::Decorator
{

    nlohmann::json RegisteredOnly::ExecutePayload(ClientHandle& clientHandle)
    {
        if (!clientHandle.m_dbUser.IsValid())
            throw Exception::UserNotRegistered();

        return  m_pDecoratedPacket->ExecutePayload(clientHandle);
    }

    RegisteredOnly::RegisteredOnly(std::unique_ptr<BasePacket> &pPacket) : BaseDecorator(pPacket)
    {

    }
} // Decorator