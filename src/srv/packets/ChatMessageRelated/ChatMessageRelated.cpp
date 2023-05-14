//
// Created by Vladislav on 3/19/2023.
//

#include "ChatMessageRelated.h"
#include "../../DataBaseAPI/DataBase.h"
#include "../exceptions.h"


namespace web::packet::message
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
        m_messageFromPacket = dbapi::DataBase::Get()->GetChatMessageById(iChatId);
    }

    dbapi::Chat ChatMessageRelated::GetChat()
    {
        return m_messageFromPacket.GetChat();
    }
}
