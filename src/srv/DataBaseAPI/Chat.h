//
// Created by alpat on 03.02.2023.
//

#pragma once
#include <string>
#include <vector>
#include "Object.h"


namespace DBAPI
{
    class User;
    class Chat final : public Object
    {
    public:
        friend class User;
        friend class DataBase;
        void SendMessage(const User& user, std::string text);
        std::vector<User> GetMembers() const;
        void AddUser(const User& user);
        void RemoveUser(const User& user);
        bool IsUserInChat(const User& user) const;
        std::string GetName() const;
        std::string GetInviteLink() const;

    private:
        Chat(int iId) {m_iID = iId;}
    };

} // DBAP
