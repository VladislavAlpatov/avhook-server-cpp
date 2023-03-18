//
// Created by alpat on 03.02.2023.
//

#pragma once


#include <string>
#include <vector>
#include "Object.h"
#include "IJsonExportable.h"



namespace DBAPI
{
    class User;
    class Chat final : public Object, public IJsonExportable
    {
    public:
        friend class User;
        friend class DataBase;
        Chat() = default;
        void SendMessage(const User& user, std::string text);


        [[nodiscard]] std::vector<User> GetMembers()      const;
        [[nodiscard]] User              GetOwner()        const;
        [[nodiscard]] bool IsUserInChat(const User& user) const;
        [[nodiscard]] std::string GetName()               const;
        [[nodiscard]] std::string GetInviteLink()         const;
        [[nodiscard]] bool HasUser(const User& user)      const;


        nlohmann::json ToJson() const override;

        void AddUser(const User& user);
        void RemoveUser(const User& user);

    private:
        Chat(int iId) {m_iID = iId;}
    };

} // DBAP
