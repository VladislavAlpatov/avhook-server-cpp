//
// Created by Vladislav on 3/19/2023.
//

#include "GetInvite.h"

namespace web::packet::chat
{
    nlohmann::json GetInvite::ExecutePayload(web::ClientHandle &clientHandle)
    {
        return {{"invite",m_chatFromPacket.GetInviteLink()}};
    }
    GetInvite::GetInvite(const nlohmann::json &data) : ChatRelated(data)
    {

    }
}
