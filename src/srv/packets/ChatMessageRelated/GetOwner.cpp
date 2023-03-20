//
// Created by Vladislav on 3/20/2023.
//

#include "GetOwner.h"

#include "../../DataBaseAPI/User.h"
#include "../../DataBaseAPI/Chat.h"

namespace Web::Packet::ChatMessage
{
    GetOwner::GetOwner(const nlohmann::json &data) : ChatMessageRelated(data)
    {

    }

    nlohmann::json GetOwner::ExecutePayload(ClientHandle &clientHandle)
    {
        return {{"id",m_messageFromPacket.GetOwner().GetID() }};
    }

}
