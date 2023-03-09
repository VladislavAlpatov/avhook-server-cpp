//
// Created by vladislav on 07.03.23.
//

#include "GetStatus.h"

namespace Web::Packet::User
{

    nlohmann::json GetStatus::ExecutePayload(ClientHandle &clientHandle)
    {
        return {{"status", m_userFromPacket.GetStatus()}};
    }

    GetStatus::GetStatus(const nlohmann::json &data) : UserRelated(data)
    {

    }
}