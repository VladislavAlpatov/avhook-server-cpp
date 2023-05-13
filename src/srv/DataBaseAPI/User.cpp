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
#include "Subscription.h"


namespace DBAPI
{
    User::User(uint64_t iUserId) : Object(iUserId)
    {

    }

    std::string User::GetName() const
    {
        auto pDataBase = DataBase::Get();
        return pDataBase->Query(fmt::format("SELECT `name` FROM `users` WHERE `id` = {}", m_iID))[0][0];
    }

    bool User::IsUserNameAcceptable(const std::string &name)
    {
		constexpr int iMaxUserNameLength = 32;

        if (name.size() > iMaxUserNameLength)
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
        pDataBase->Query(fmt::format("UPDATE `users` SET `status` = '{}' WHERE `id` = {}",sStatus, m_iID ));

    }

    std::vector<Chat> User::GetChatList() const
    {
        auto pDataBase = DataBase::Get();
        std::vector<Chat> chats;

        const auto chatIds = pDataBase->Query(fmt::format("SELECT `chat_id` FROM `chats-members` WHERE `user_id` = {}", m_iID));

        chats.reserve(chatIds.size());

        for (const auto& data : chatIds)
            chats.push_back({std::stoull(data[0])});

        return chats;
    }

    void User::SetName(std::string sName)
    {
        auto pDataBase = DataBase::Get();

        if (!IsUserNameAcceptable(sName))
            throw Exception::UserNameIsInvalid();

		// Prevent SQL injection using string valuability
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

    int User::GetRights() const
    {
        auto pDataBase = DataBase::Get();

        const auto data = pDataBase->Query(fmt::format("SELECT `type` FROM `users` WHERE `id` = {}", m_iID));
        const auto iRights =  std::stoi(data[0][0]);

        return iRights;
    }

    bool User::HasRightsOf(int iRights) const
    {
        return GetRights() & iRights;
    }

    void User::SetRights(int iRights) const
    {
        DataBase::Get()->Query(fmt::format("UPDATE `users` SET `type` = {} WHERE `id` = {}", iRights, m_iID));
    }

    void User::AddRights(int iRights) const
    {
        SetRights(GetRights() | iRights);
    }

	std::vector<Subscription> User::GetSubscriptions() const
	{
		const auto data = DataBase::Get()->Query(fmt::format("SELECT `id` FROM `subscriptions` WHERE `user_id` = {}", m_iID));
		std::vector<Subscription> out;
		out.reserve(data[0].size());

		for (const auto& id : data[0])
			out.push_back({std::stoull(id)});

		return out;
	}
} // DBAPI