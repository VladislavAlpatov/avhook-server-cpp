//
// Created by Vladislav on 3/19/2023.
//

#include "SendMessage.h"
#include "../exceptions.h"
#include "../../ClientHandle/ClientHandle.h"

namespace web::packet::chat
{
    nlohmann::json SendMessage::ExecutePayload(web::ClientHandle &clientHandle)
    {
        m_chatFromPacket.SendMessage(clientHandle.m_dbUser, m_sMessageText);
        return {};
    }

    SendMessage::SendMessage(const nlohmann::json &data) : ChatRelated(data)
    {
        try
        {
            m_sMessageText = data.at("message");
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }
}
