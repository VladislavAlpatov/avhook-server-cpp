//
// Created by Vladislav on 3/18/2023.
//

#include "ChatRelated.h"
#include "../../DataBaseAPI/DataBase.h"
#include "../exceptions.h"


namespace Web::Packet::Chat
{
    ChatRelated::ChatRelated(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            DBAPI::DataBase::Get()->GetChatById(data["id"]);
        }
        catch (const nlohmann::json::exception& ex )
        {
            throw Packet::Exception::CorruptedPacket();
        }
    }
}
