//
// Created by alpat on 20.01.2023.
//

#include "RegisteredOnly.h"
#include "exceptions.h"

namespace web::packet::decorator
{

    nlohmann::json RegisteredOnly::ExecutePayload(ClientHandle& clientHandle)
    {
        if (!clientHandle.m_dbUser.IsValid())
            throw Exception::UserNotRegistered();

        return  m_pDecoratedPacket->ExecutePayload(clientHandle);
    }

    RegisteredOnly::RegisteredOnly(std::unique_ptr<IPayloadExecutable> &pPacket) : BaseDecorator(pPacket)
    {

    }
} // decorator