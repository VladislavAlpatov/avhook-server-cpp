//
// Created by alpat on 03.02.2023.
//

#pragma once

#include "../../lib/sqlite/connection.h"


namespace DBAPI
{
    class User;
    class Chat;

    class DataBase : public sql::Connection
    {
    public:
        static DataBase* Get();
        DBAPI::User GetUserById(int iUserId);
        bool        IsUserExist(int iUserId);
        bool        IsChatExist(int iChatId);
        Chat        GetChatById(int iChatId) ;
        User        GetUserByEmail(std::string sEmail);

        void AddNewUser(const std::string& sName, const std::string& sStatus,const std::string& sPassword, const std::string sEmail, int iType);
    private:
        DataBase(const std::string& sPath);
    };

} // DBAPI
