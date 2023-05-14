//
// Created by vladislav on 07.03.23.
//

#include "GetStatus.h"

namespace web::packet::user
{

    nlohmann::json GetStatus::ExecutePayload(ClientHandle &clientHandle)
    {
        return {{"status", m_pUserFromPacket.GetStatus()}};
    }

    GetStatus::GetStatus(const nlohmann::json &data) : UserRelated(data)
    {

    }
}