//
// Created by Vladislav on 3/19/2023.
//

#include "ChatMessage.h"
#include "User.h"
#include "Chat.h"
#include "DataBase.h"

#include <fmt/format.h>
#include <boost/algorithm/string.hpp>


DBAPI::User DBAPI::ChatMessage::GetOwner() const
{
    const auto pDataBase = DataBase::Get();
    auto data = pDataBase->Query(fmt::format("SELECT `owner_id` FROM `chats-messages` WHERE `id` = {}", m_iID));

    return pDataBase->GetUserById(std::stoull(data[0][0]));
}

DBAPI::Chat DBAPI::ChatMessage::GetChat() const
{
    const auto pDataBase = DataBase::Get();
    auto data = pDataBase->Query(fmt::format("SELECT `chat_id` FROM `chats-messages` WHERE `id` = {}", m_iID));

    return pDataBase->GetChatById(std::stoull(data[0][0]));
}

std::string DBAPI::ChatMessage::GetText() const
{
    const auto pDataBase = DataBase::Get();
    const auto data = pDataBase->Query(fmt::format("SELECT `text` FROM `chats-messages` WHERE `id` = {}", m_iID));
    return data[0][0];
}

void DBAPI::ChatMessage::SetText(std::string text)
{
    const auto pDataBase = DataBase::Get();

    boost::replace_all(text, "'", "''");
    pDataBase->Query(fmt::format("UPDATE `chats-messages` SET `text` = '{}' FROM  WHERE `id` = {}",text, m_iID));
}

DBAPI::ChatMessage::ChatMessage(uint64_t id) : Object(id)
{

}
