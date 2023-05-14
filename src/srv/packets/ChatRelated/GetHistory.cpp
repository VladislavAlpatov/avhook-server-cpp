//
// Created by Vladislav on 3/19/2023.
//

#include "GetHistory.h"
#include "../../DataBaseAPI/ChatMessage.h"


namespace web::packet::chat
{
    GetHistory::GetHistory(const nlohmann::json &data) : ChatRelated(data)
    {

    }

    nlohmann::json GetHistory::ExecutePayload(ClientHandle &clientHandle)
    {
        std::vector<nlohmann::json> messagesJson;

        const auto msgs = m_chatFromPacket.GetHistory();
        messagesJson.reserve(msgs.size());

        for (const auto& message : msgs)
            messagesJson.push_back({{"id", message.GetID()}});

        return {{"messages", messagesJson}};
    }
}

