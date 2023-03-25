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
    class ChatMessage;
    class Chat final : public Object, public IJsonExportable
    {
    public:
        friend class User;
        friend class DataBase;
        Chat() = default;
        void SendMessage(const User& user, std::string text);

        [[nodiscard]] bool                     IsMessageTextValid(const std::string& msg)                      const;
        [[nodiscard]] std::vector<User>        GetMembers()                                                    const;
        [[nodiscard]] User                     GetOwner()                                                      const;
        [[nodiscard]] bool                     IsUserInChat(const User& user)                                  const;
        [[nodiscard]] std::string              GetName()                                                       const;
        [[nodiscard]] std::string              GetInviteLink()                                                 const;
        [[nodiscard]] bool                     HasUser(const User& user)                                       const;
        [[nodiscard]] std::vector<ChatMessage> GetHistory()                                                    const;
        [[nodiscard]] std::vector<ChatMessage> GetMessagesAfter(const ChatMessage& msg, uint64_t limit)        const;
        [[nodiscard]] ChatMessage              GetLastMessage()                                                const;
        

        nlohmann::json ToJson() const override;

        void AddUser(const User& user);
        void RemoveUser(const User& user);

    private:
        Chat(uint64_t iId) : Object(iId){}
    };

} // DBAP
