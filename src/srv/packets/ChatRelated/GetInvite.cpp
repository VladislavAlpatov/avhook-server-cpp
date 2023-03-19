//
// Created by Vladislav on 3/19/2023.
//

#include "GetInvite.h"

namespace Web::Packet::Chat
{
    nlohmann::json GetInvite::ExecutePayload(Web::ClientHandle &clientHandle)
    {
        return {{"invite",m_chatFromPacket.GetInviteLink()}};
    }
    GetInvite::GetInvite(const nlohmann::json &data) : ChatRelated(data)
    {

    }
}
