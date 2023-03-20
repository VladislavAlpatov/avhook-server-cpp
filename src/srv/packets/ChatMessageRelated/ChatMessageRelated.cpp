//
// Created by Vladislav on 3/19/2023.
//

#include "ChatMessageRelated.h"
#include "../../DataBaseAPI/DataBase.h"
#include "../exceptions.h"


namespace Web::Packet::ChatMessage
{
    ChatMessageRelated::ChatMessageRelated(const nlohmann::json &data) : BasePacket(data)
    {
        int iChatId;
        try
        {
            iChatId = data["id"];
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
        m_messageFromPacket = DBAPI::DataBase::Get()->GetChatMessageById(iChatId);
    }

    DBAPI::Chat ChatMessageRelated::GetChat()
    {
        return m_messageFromPacket.GetChat();
    }
}
