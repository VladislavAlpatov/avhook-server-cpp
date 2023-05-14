//
// Created by Vladislav on 3/19/2023.
//

#include "SetStatus.h"
#include "../exceptions.h"
#include "../../ClientHandle/ClientHandle.h"

namespace web::packet::user
{

    SetStatus::SetStatus(const nlohmann::json &data) : UserRelated(data)
    {
        try
        {
            m_newStatus = data.at("status");
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }

    nlohmann::json SetStatus::ExecutePayload(ClientHandle &clientHandle)
    {
        clientHandle.m_dbUser.SetStatus(m_newStatus);
        return {};
    }
}