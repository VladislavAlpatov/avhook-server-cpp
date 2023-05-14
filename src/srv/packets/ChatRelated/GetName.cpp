//
// Created by Vladislav on 3/18/2023.
//

#include "GetName.h"
#include "../../ClientHandle/ClientHandle.h"

namespace web::packet::chat
{
    nlohmann::json GetName::ExecutePayload(web::ClientHandle &clientHandle)
    {
        return {{"name", m_chatFromPacket.GetName()}};
    }

    GetName::GetName(const nlohmann::json &data) : ChatRelated(data)
    {

	}
}
