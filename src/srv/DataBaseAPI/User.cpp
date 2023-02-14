//
// Created by alpat on 03.02.2023.
//

#include "User.h"
#include "DataBase.h"
#include <fmt/format.h>
#include <boost/algorithm/string.hpp>
#include "Chat.h"

namespace DBAPI
{
    User::User(int iUserId)
    {
        m_iID = iUserId;
    }

    std::string User::GetName() const
    {
        auto pDataBase = DataBase::Get();
        return pDataBase->Query(fmt::format("SELECT `name` FROM `users` WHERE `id` = {}", m_iID))[0][0];
    }

    bool User::IsUserNameAcceptable(const std::string &name) const
    {
        if (name.size() > 32)
            return false;


        return !std::any_of(name.begin(), name.end(), [](char chr) {return (chr == ' ' or chr == '\n' or chr == '\t'); });
    }

    std::string User::GetStatus() const
    {
        auto pDataBase = DataBase::Get();
        return pDataBase->Query(fmt::format("SELECT `status` FROM `users` WHERE `id` = {}", m_iID))[0][0];
    }

    int User::GetType() const
    {
        auto pDataBase = DataBase::Get();
        return std::stoi(pDataBase->Query(fmt::format("SELECT `type` FROM `users` WHERE `id` = {}", m_iID))[0][0]);
    }

    std::string User::GetPassword() const
    {
        auto pDataBase = DataBase::Get();
        return pDataBase->Query(fmt::format("SELECT `password` FROM `users` WHERE `id` = {}", m_iID))[0][0];
    }

    std::string User::GetEmail() const
    {
        auto pDataBase = DataBase::Get();
        return pDataBase->Query(fmt::format("SELECT `email` FROM `users` WHERE `id` = {}", m_iID))[0][0];
    }

    void User::SetStatus(std::string sStatus)
    {
        auto pDataBase = DataBase::Get();

        boost::replace_all(sStatus, "'", "''");
        boost::replace_all(sStatus, "\"", "\"\"");
        pDataBase->Query(fmt::format("UPDATE `users` SET `status` = '{}' WHERE `id` = {}",sStatus, m_iID ));

    }

    std::vector<Chat> User::GetChatList() const
    {
        auto pDataBase = DataBase::Get();
        std::vector<Chat> chats;

        const auto chatIds = pDataBase->Query(fmt::format("SELECT `chat_id` FROM `chats-members` WHERE `user_id` = {}", m_iID));

        chats.reserve(chatIds.size());

        for (const auto& data : chatIds)
            chats.push_back({std::stoi(data[0])});

        return chats;
    }
} // DBAPI