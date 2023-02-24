//
// Created by alpat on 03.02.2023.
//

#pragma once

#include <string>
#include <vector>

#include "Object.h"


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
        [[nodiscard]] static bool                     IsUserNameAcceptable(const std::string& name)       ;
        [[nodiscard]] std::vector<Chat>        GetChatList()                                       const;
        [[nodiscard]] bool                     IsValid() const {return m_iID != INVALID_USER_ID;};


        void SetName(std::string sName);
        void SetStatus(std::string sStatus);
        void SetType(int iType);
        void SetEmail(std::string sEmail);
        void CreateChat(const std::string& sName);
    private:
        User(int iUserId);
    };

} // DBAPI
