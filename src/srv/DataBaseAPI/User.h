//
// Created by alpat on 03.02.2023.
//

#pragma once
#include <string>
#include "Object.h"
#include <vector>
#define INVALID_USER_ID (-1)


namespace DBAPI
{
    class Chat;
    class Config;
    class User final : public Object
    {
        friend class DataBase;
        friend class Chat;
    public:
        User() = default;
        std::string GetName()     const;
        std::string GetStatus()   const;
        int         GetType()     const;
        std::string GetPassword() const;
        std::string GetEmail()    const;
        std::vector<Config>      GetConfigs()   const;
        bool IsValid() const {return m_iID != INVALID_USER_ID;};
        void SetName(std::string sName);
        void SetStatus(std::string sStatus);
        void SetType(int iType);
        void SetEmail(std::string sEmail);
        bool IsUserNameAcceptable(const std::string& name) const;
        std::vector<Chat> GetChatList() const;
    private:
        User(int iUserId);
    };

} // DBAPI
