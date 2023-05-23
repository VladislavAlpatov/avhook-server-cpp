//
// Created by alpat on 03.02.2023.
//

#include "DataBase.h"

#include "exceptions.h"
#include "User.h"
#include "Chat.h"
#include "ChatMessage.h"
#include "Config.h"
#include "ActivationKey.h"
#include "Subscription.h"
#include "Product.h"


#include <boost/algorithm/string.hpp>
#include <random>
#include <memory>
#include <fmt/format.h>


uint64_t GeneratePublicId()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<uint64_t> uni(0,UINT64_MAX);

    return uni(rng);
}

namespace dbapi
{
    dbapi::User DataBase::GetUserById(uint64_t iUserId)
    {
        if (!IsUserExist(iUserId))
            throw Exception::UserNotFound();

        return {iUserId};
    }

    DataBase* DataBase::Get()
    {
#ifndef NDEBUG
        static auto pDataBase = std::unique_ptr<DataBase>(new DataBase("/home/vlad/databases/db.db"));
#else
        static auto pDataBase = std::unique_ptr<DataBase>(new DataBase("/databases/db.db"));
#endif
        return pDataBase.get();
    }

    DataBase::DataBase(const std::string& sPath) : sql::Connection(sPath)
    {

    }

    bool DataBase::IsUserExist(uint64_t iUserId)
    {
        return !Query(fmt::format("SELECT `id` FROM `users` WHERE `id` = {}", iUserId)).empty();
    }

    bool DataBase::IsChatExist(uint64_t iChatId)
    {
        return !Query(fmt::format("SELECT `id` FROM `chats` WHERE `id` = {}", iChatId)).empty();
    }

    Chat DataBase::GetChatById(uint64_t iChatId)
    {
        if (!IsChatExist(iChatId))
            throw Exception::ChatNotFound();

        auto id = std::stoull(Query(fmt::format("SELECT `id` FROM `chats` WHERE `id` = {}", iChatId))[0][0]);
        return {id};
    }

    User DataBase::GetUserByEmail(std::string sEmail)
    {
        boost::replace_all(sEmail, "'", "''");
        boost::replace_all(sEmail, "\"", "\"\"");

        const auto data = Query(fmt::format("SELECT `id` FROM `users` WHERE `email` = '{}'", sEmail));

        if (data.empty())
            throw Exception::UserNotFound();


        return {std::stoull(data[0][0])};
    }

    void DataBase::CreateChat(const User &owner, const std::string &sName)
    {
        uint64_t publicId = 0;

        do
        {
            publicId = GeneratePublicId();

        } while (IsPrivateChatLinkTaken(publicId));

        Query(fmt::format("INSERT INTO `chats` (`owner_id`, `name`, `public_id`) VALUES({},'{}',{})", owner.m_iID, sName, publicId));
    }

    bool DataBase::IsPrivateChatLinkTaken(uint64_t link)
    {
        return !Query(fmt::format("SELECT `id` FROM `chats` WHERE `public_id` = {}", link)).empty();
    }

    ChatMessage DataBase::GetChatMessageById(uint64_t id)
    {
        if (!IsChatMessageExist(id))
            throw Exception::ChatMessageNotFound();

        return {id};
    }

    bool DataBase::IsChatMessageExist(uint64_t iMessageId)
    {
        return !Query(fmt::format("SELECT `id` FROM `chats-messages` WHERE `id` = {}", iMessageId)).empty();
    }

    Config DataBase::GetConfigById(uint64_t id)
    {
        if (!IsConfigExist(id))
            throw  Exception::ConfigNotFound();

        return {id };
    }

    bool DataBase::IsConfigExist(uint64_t id)
    {
        return !Query(fmt::format("SELECT `id` FROM `configs` WHERE `id` = {}", id)).empty();
    }

	ActivationKey DataBase::GetActivationKeyById(uint64_t id)
	{
		return {id};
	}

	bool DataBase::IsSubscriptionExist(uint64_t iSubId)
	{
		return !Query(fmt::format("SELECT `id` FROM `subscriptions` WHERE `id` = {}", iSubId)).empty();
	}

	Subscription DataBase::GetSubscriptionById(uint64_t iUserId)
	{
		if (!IsSubscriptionExist(iUserId))
			throw std::runtime_error("subscription with this id dosent exist!");

		return {iUserId};
	}

	bool DataBase::IsProductExist(uint64_t iProductId)
	{
		return !Query(fmt::format("SELECT `id` FROM `products` WHERE `id` = {}", iProductId)).empty();
	}

	Product DataBase::GetProductById(uint64_t iProductId)
	{
		if (!IsProductExist(iProductId))
			throw std::runtime_error("subscription with this id dosent exist!");

		return {std::stoull(Query(fmt::format("SELECT `id` FROM `products` WHERE `id` = {}", iProductId))[0][0])};
	}

	std::vector<Product> DataBase::GetProductList()
	{
		std::vector<Product> out;
		for (const auto& row : Query("SELECT `id` FROM `products`"))
			out.push_back({std::stoull(row[0])});
		return out;
	}
} // DBAP