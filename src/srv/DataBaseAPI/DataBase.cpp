//
// Created by alpat on 03.02.2023.
//

#include "DataBase.h"

#include "exceptions.h"
#include "User.h"
#include "Chat.h"
#include "ChatMessage.h"


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

namespace DBAPI
{
    DBAPI::User DataBase::GetUserById(int iUserId)
    {
        if (!IsUserExist(iUserId))
            throw Exception::UserNotFound();

        return {iUserId};
    }

    DataBase* DataBase::Get()
    {
        static auto pDataBase = std::unique_ptr<DataBase>(new DataBase("/home/vlad/Desktop/db.db"));

        return pDataBase.get();
    }

    DataBase::DataBase(const std::string& sPath) : sql::Connection(sPath)
    {

    }

    bool DataBase::IsUserExist(int iUserId)
    {
        return !Query(fmt::format("SELECT `id` FROM `users` WHERE `id` = {}", iUserId)).empty();
    }

    bool DataBase::IsChatExist(int iChatId)
    {
        return !Query(fmt::format("SELECT `id` FROM `chats` WHERE `id` = {}", iChatId)).empty();
    }

    Chat DataBase::GetChatById(int iChatId)
    {
        if (!IsChatExist(iChatId))
            throw Exception::ChatNotFound();

        int id = std::stoi(Query(fmt::format("SELECT `id` FROM `chats` WHERE `id` = {}", iChatId))[0][0]);
        return {id};
    }

    User DataBase::GetUserByEmail(std::string sEmail)
    {
        boost::replace_all(sEmail, "'", "''");
        boost::replace_all(sEmail, "\"", "\"\"");

        const auto data = Query(fmt::format("SELECT `id` FROM `users` WHERE `email` = '{}'", sEmail));

        if (data.empty())
            throw Exception::UserNotFound();


        return {std::stoi(data[0][0])};
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

    ChatMessage DataBase::GetChatMessageById(int iChatMessage)
    {
        if (!IsChatMessageExist(iChatMessage))
            throw Exception::ChatMessageNotFound();

        const auto data = Query(fmt::format("SELECT `id` FROM `chats-messages` WHERE `id` = {}", iChatMessage));

        return {std::stoi(data[0][0])};
    }

    bool DataBase::IsChatMessageExist(int iMessageId)
    {
        return !Query(fmt::format("SELECT `id` FROM `chats-messages` WHERE `id` = {}", iMessageId)).empty();
    }
} // DBAP