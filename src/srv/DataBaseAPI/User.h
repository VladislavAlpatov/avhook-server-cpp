//
// Created by alpat on 03.02.2023.
//

#pragma once

#include <string>
#include <vector>

#include "Object.h"
#include "IJsonExportable.h"


namespace dbapi
{
    class Chat;
    class Config;
	class Subscription;

    class User final : public Object, public IJsonExportable
    {
        friend class DataBase;
        friend class Chat;
        friend class Config;


    public:
        User() = default;
        [[nodiscard]] std::string               GetName()                                           const;
        [[nodiscard]] std::string               GetStatus()                                         const;
        [[nodiscard]] int                       GetType()                                           const;
        [[nodiscard]] std::string               GetPassword()                                       const;
        [[nodiscard]] std::string               GetEmail()                                          const;
        [[nodiscard]] std::vector<Config>       GetConfigs()                                        const;
        [[nodiscard]] std::vector<Chat>         GetChatList()                                       const;
        [[nodiscard]] int                       GetRights()                                         const;
        [[nodiscard]] bool                      HasRightsOf(int iRights)                            const;
		[[nodiscard]] std::vector<Subscription> GetSubscriptions()								    const;

        void                                   SetRights(int iRights)                               const;
        void                                   AddRights(int iRights)                               const;

        [[nodiscard]] static bool              IsUserNameAcceptable(const std::string& name);
        [[nodiscard]] bool                     IsValid() const {return m_iID != INVALID_DATABASE_OBJECT_ID;};


        void SetName(std::string sName);
        void SetStatus(std::string sStatus);
        void SetType(int iType);
        void SetEmail(std::string sEmail);
        void CreateChat(const std::string& sName);


        bool operator==(const User& other) const;
        bool operator!=(const User& other) const;


        [[nodiscard]] nlohmann::json ToJson() const override;


        enum Rights : int
        {
            Basic,
            BetaTester,
            Admin,
            Developer,
        };
    private:
        User(uint64_t iUserId);
    };

} // dbapi
