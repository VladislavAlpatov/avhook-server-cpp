//
// Created by alpat on 03.02.2023.
//

#include "Chat.h"
#include "DataBase.h"
#include <fmt/format.h>
#include "exceptions.h"
#include <boost/algorithm/string.hpp>

#include "User.h"

namespace DBAPI
{
    bool Chat::IsUserInChat(const User &user) const
    {
        auto pDataBase = DataBase::Get();

        const auto str = fmt::format("SELECT `user_id` FROM `chats-members` WHERE `chat_id` = {} AND `user_id` = {}", m_iID, user.GetID());

        return !pDataBase->Query(str).empty();
    }

    void Chat::SendMessage(const User &user, std::string text)
    {
        if (!IsUserInChat(user))
            throw Exception::UserNotInChat();

        auto pDataBase = DataBase::Get();

        // Fix string for SQLite if it contains ' or "
        boost::replace_all(text, "'", "''");
        boost::replace_all(text, "\"", "\"\"");
        const auto str = fmt::format("INSET INTO `chats-messages` (`owner_id`, `chat_id`, `text`) VALUES({},{},'{}')",user.GetID(), m_iID, text);
        pDataBase->Query(str);
    }

    std::vector<User> Chat::GetMembers() const
    {
        auto pDataBase = DataBase::Get();
        std::vector<User> out;
        const auto str = fmt::format("SELECT `user_id` FROM `chats-members` WHERE `user_id` = {}", m_iID);
        const auto ids = pDataBase->Query(str);

        out.reserve(ids.size());
        for (const auto& sId : ids)
            out.push_back(pDataBase->GetUserById(std::stoi(sId[0])));

        return out;
    }
} // DBAP