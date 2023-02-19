//
// Created by Vlad on 1/5/2023.
//

#include "SendChatMessage.h"
#include "exceptions.h"
#include "../ClientHandle/ClientHandle.h"
#include "../DataBaseAPI/DataBase.h"
#include "../DataBaseAPI/Chat.h"
#include "../DataBaseAPI/User.h"


namespace Web::Packet
{

    SendChatMessage::SendChatMessage(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            m_sText   = data["text"].get<std::string>();
            m_iChatId = data["chat_id"].get<int>();
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }

    nlohmann::json SendChatMessage::ExecutePayload(ClientHandle &clientHandle)
    {
        const auto pDataBase = DBAPI::DataBase::Get();

        auto chat  = pDataBase->GetChatById(m_iChatId);

        chat.SendMessage(clientHandle.m_dbUser, m_sText);
        return {};
    }
} // Packets
