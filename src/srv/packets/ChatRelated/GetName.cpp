//
// Created by Vladislav on 3/18/2023.
//

#include "GetName.h"
#include "../../ClientHandle/ClientHandle.h"

namespace Web::Packet::Chat
{
    nlohmann::json GetName::ExecutePayload(Web::ClientHandle &clientHandle)
    {
        return {{"name", m_chatFromPacket.GetName()}};
    }

    GetName::GetName(const nlohmann::json &data) : ChatRelated(data)
    {

	}
}
