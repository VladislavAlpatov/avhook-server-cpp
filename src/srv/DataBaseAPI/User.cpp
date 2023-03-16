//
// Created by alpat on 03.02.2023.
//

#include "User.h"
#include "DataBase.h"
#include <fmt/format.h>
#include <boost/algorithm/string.hpp>
#include "Chat.h"
#include "Config.h"
#include "exceptions.h"


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

    bool User::IsUserNameAcceptable(const std::string &name)
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

    void User::SetName(std::string sName)
    {
        auto pDataBase = DataBase::Get();

        if (!IsUserNameAcceptable(sName))
            throw std::runtime_error("Username is invalid");

        boost::replace_all(sName, "'", "''");

        pDataBase->Query(fmt::format("UPDATE `users` SET `name` = '{}' WHERE `id` = {}",sName, m_iID));


    }

    void User::SetType(int iType)
    {
        auto pDataBase = DataBase::Get();
        pDataBase->Query(fmt::format("UPDATE `users` SET `type` = {} WHERE `id` = {}", iType, m_iID));

    }

    void User::SetEmail(std::string sEmail)
    {
        auto pDataBase = DataBase::Get();

        boost::replace_all(sEmail, "'", "''");
        pDataBase->Query(fmt::format("UPDATE `users` SET `email` = '{}' WHERE `id` = {}", sEmail, m_iID));
    }

    std::vector<Config> User::GetConfigs() const
    {
        auto pDataBase = DataBase::Get();

        std::vector<Config> cfgs;
        const auto data = pDataBase->Query(fmt::format("SELECT `id` FROM `configs` WHERE `owner_id` = {}", m_iID));
        cfgs.reserve(data.size());

        for (const auto& cfg : data)
            cfgs.emplace_back(std::stoi(cfg[0]));

        return cfgs;

    }

    void User::CreateChat(const std::string &sName)
    {
        DataBase::Get()->CreateChat(*this,sName);
    }

    nlohmann::json User::ToJson() const
    {

        return {

                {"id",     GetID()},
                {"name",   GetName()},
                {"status", GetStatus()},
                {"type",   GetType()},

        };
    }

    bool User::operator==(const User &other) const
    {
        return m_iID == other.m_iID;
    }

    bool User::operator!=(const User &other) const
    {
        return !(*this == other);
    }
} // DBAPI