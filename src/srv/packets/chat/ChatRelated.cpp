//
// Created by Vladislav on 3/18/2023.
//

#include "ChatRelated.h"
#include "../../DataBaseAPI/DataBase.h"
#include "../exceptions.h"


namespace web::packet::chat
{
    ChatRelated::ChatRelated(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            m_chatFromPacket = dbapi::DataBase::Get()->GetChatById(data["id"]);
        }
        catch (const nlohmann::json::exception& ex )
        {
            throw packet::Exception::CorruptedPacket();
        }
    }

    dbapi::Chat ChatRelated::GetChat()
    {
        return m_chatFromPacket;
    }
}
