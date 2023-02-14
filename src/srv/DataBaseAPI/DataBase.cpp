//
// Created by alpat on 03.02.2023.
//

#include "DataBase.h"
#include <memory>
#include <fmt/format.h>
#include "exceptions.h"
#include "User.h"
#include "Chat.h"
#include <boost/algorithm/string.hpp>


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
        static auto pDataBase = std::unique_ptr<DataBase>(new DataBase("db.db"));

        return pDataBase.get();
    }

    DataBase::DataBase(const std::string& sPath) : sql::Connection(sPath)
    {

    }

    bool DataBase::IsUserExist(int iUserId)
    {
        return !Query(fmt::format("SELECT `id FROM `users` WHERE `id` = {}", iUserId)).empty();
    }

    bool DataBase::IsChatExist(int iChatId)
    {
        return !Query(fmt::format("SELECT `id FROM `chats` WHERE `id` = {}", iChatId)).empty();
    }

    Chat DataBase::GetChatById(int iChatId)
    {
        return {0};
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
} // DBAP