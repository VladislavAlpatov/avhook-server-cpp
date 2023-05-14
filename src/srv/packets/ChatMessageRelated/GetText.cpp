//
// Created by Vladislav on 3/19/2023.
//

#include "GetText.h"
namespace web::packet::message
{
    GetText::GetText(const nlohmann::json &data) : ChatMessageRelated(data)
    {

    }

    nlohmann::json GetText::ExecutePayload(ClientHandle &clientHandle)
    {
        return {{"text", m_messageFromPacket.GetText()}};
    }
}