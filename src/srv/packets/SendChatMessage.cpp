//
// Created by Vlad on 1/5/2023.
//

#include "SendChatMessage.h"
#include "exceptions.h"
#include "../../lib/sqlite/connection.h"
#include <fmt/format.h>
#include <boost/algorithm/string/replace.hpp>
#include "../ClientHandle/ClientHandle.h"

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
        auto  pDataBase = sql::Connection::Get();

        if(pDataBase->Query(fmt::format("SELECT `id` FROM `chats` WHERE `id` = {}", m_iChatId)).empty())
            throw Exception::ChatDoesNotExist();


        if (pDataBase->Query(fmt::format("SELECT `user_id` FROM `chats-members` WHERE `user_id` = {} AND `chat_id` = {}",
                                         clientHandle.m_iUserId, m_iChatId)).empty())
            throw Exception::ChatDoesNotExist();

        // Fix string for SQLite if it contains ' or "
        boost::replace_all(m_sText, "'", "''");
        boost::replace_all(m_sText, "\"", "\"\"");

        pDataBase->Query(fmt::format("INSERT INTO `chat-messages` (`owner_id`, `chat_id`, `text`) VALUES({},{},'{}')", clientHandle.m_iUserId, m_iChatId, m_sText));

        return {};
    }
} // Packets
