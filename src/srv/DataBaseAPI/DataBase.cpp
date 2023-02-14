//
// Created by alpat on 03.02.2023.
//

#include "DataBase.h"
#include <memory>
#include <fmt/format.h>
#include "exceptions.h"
#include "User.h"
#include "Chat.h"

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
        return !Query(fmt::format("SELECT `id FROM `chats` WHERE `id` = {}", iChatId)).empty();;
    }

    Chat DataBase::GetChatById(int iChatId)
    {
        return Chat(0);
    }
} // DBAP