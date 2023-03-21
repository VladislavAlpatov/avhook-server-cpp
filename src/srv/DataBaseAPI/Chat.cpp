//
// Created by alpat on 03.02.2023.
//

#include "Chat.h"
#include "DataBase.h"
#include <fmt/format.h>
#include "exceptions.h"
#include <boost/algorithm/string.hpp>
#include "../../lib/base64/base64.h"


#include "ChatMessage.h"
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
        if (!IsMessageTextValid(text))
            throw Exception::ChatMessageIsNotValid();

        if (!IsUserInChat(user))
            throw Exception::UserNotInChat();

        auto pDataBase = DataBase::Get();
        // Fix string for SQLite if it contains ' or "
        boost::replace_all(text, "'", "''");
        const auto str = fmt::format("INSERT INTO `chats-messages` (`owner_id`, `chat_id`, `text`) VALUES({},{},'{}')", user.GetID(), m_iID, text);
        pDataBase->Query(str);
    }

    std::vector<User> Chat::GetMembers() const
    {
        auto pDataBase = DataBase::Get();
        std::vector<User> out;
        const auto str = fmt::format("SELECT `user_id` FROM `chats-members` WHERE `chat_id` = {}", m_iID);
        const auto ids = pDataBase->Query(str);

        out.reserve(ids.size());
        for (const auto& sId : ids)
            out.push_back(pDataBase->GetUserById(std::stoi(sId[0])));

        return out;
    }

    std::string Chat::GetName() const
    {
        auto pDataBase = DataBase::Get();

        return pDataBase->Query(fmt::format("SELECT `name` FROM `chats` WHERE `id` = {}", m_iID))[0][0];
    }

    std::string Chat::GetInviteLink() const
    {
        auto pDataBase = DataBase::Get();
        const auto data = pDataBase->Query(fmt::format("SELECT `public_id` FROM `chats` WHERE `id` = {}", m_iID));

        return base64::code(std::stoi(data[0][0]));
    }

    User Chat::GetOwner() const
    {
        auto pDataBase = DataBase::Get();

        const auto data = pDataBase->Query(fmt::format("SELECT `owner_id` FROM `chats` WHERE `id` = {}", m_iID));

        return {std::stoi(data[0][0])};
    }

    void Chat::AddUser(const User &user)
    {
        if (IsUserInChat(user))
            throw Exception::UserAlreadyInChat();

        auto pDataBase = DataBase::Get();

        pDataBase->Query(fmt::format("INSERT INTO `chats-members` (`user_id`, `chat_id`) VALUES({},{})",user.GetID(), m_iID));
    }

    nlohmann::json Chat::ToJson() const
    {
        nlohmann::json data = {

                {"name",      GetName()},
                {"id",         GetID()},
                {"owner",      GetOwner().ToJson()},
                {"invite_link",GetInviteLink()},
        };

        return data;
    }

    bool Chat::HasUser(const User &user) const
    {
        for (const auto& chatMember : GetMembers())
            if (user == chatMember)
                return true;
        return false;
    }

    std::vector<ChatMessage> Chat::GetHistory() const
    {
        std::vector<ChatMessage> out;
        const auto data = DataBase::Get()->Query(fmt::format("SELECT `id` FROM `chats-messages` WHERE `chat_id` = {}", m_iID));
        out.reserve(data.size());

        for (const auto& row : data)
            out.push_back({std::stoi(row[0])});

        return out;
    }

    bool Chat::IsMessageTextValid(const std::string& msg) const
    {
        return msg.empty() or msg.length() > 2048 or std::all_of(msg.begin(), msg.end(),[](const char chr) {return chr == '\n';});
    }
} // DBAP