//
// Created by vladislav on 07.03.23.
//

#include "GetName.h"


#include "../../DataBaseAPI/DataBase.h"

namespace web::packet::user
{
    nlohmann::json GetName::ExecutePayload(ClientHandle &clientHandle)
    {

        return {{"name", m_pUserFromPacket.GetName()}};
    }

    GetName::GetName(const nlohmann::json &data) : UserRelated(data)
    {

    }
} // User