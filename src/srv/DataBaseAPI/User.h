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
        [[nodiscard]] std::string              GetName()                                           const;
        [[nodiscard]] std::string              GetStatus()                                         const;
        [[nodiscard]] int                      GetType()                                           const;
        [[nodiscard]] std::string              GetPassword()                                       const;
        [[nodiscard]] std::string              GetEmail()                                          const;
        [[nodiscard]] std::vector<Config>      GetConfigs()                                        const;
        [[nodiscard]] bool                     IsUserNameAcceptable(const std::string& name)       const;
        [[nodiscard]] std::vector<Chat>        GetChatList()                                       const;
        [[nodiscard]] bool                     IsValid() const {return m_iID != INVALID_USER_ID;};
        void SetName(std::string sName);
        void SetStatus(std::string sStatus);
        void SetType(int iType);
        void SetEmail(std::string sEmail);
    private:
        User(int iUserId);
    };

} // DBAPI
