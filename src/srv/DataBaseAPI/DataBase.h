//
// Created by alpat on 03.02.2023.
//

#pragma once

#include "../../lib/sqlite/connection.h"


namespace dbapi
{
    class User;
    class Chat;
    class ChatMessage;
    class Config;
	class ActivationKey;
	class Subscription;
	class Product;
    class DataBase final : public sql::Connection
    {
    public:
        static DataBase* Get();
        User GetUserById(uint64_t iUserId);
		Subscription GetSubscriptionById(uint64_t iUserId);
        bool        IsUserExist(uint64_t iUserId);
		bool 		IsSubscriptionExist(uint64_t iSubId);
        bool        IsChatExist(uint64_t iChatId);
        bool        IsPrivateChatLinkTaken(uint64_t link);
        bool        IsChatMessageExist(uint64_t iMessageId);
		bool        IsProductExist(uint64_t iProductId);
		Product		GetProductById(uint64_t iProductId);
		std::vector<Product> GetProductList();
        Chat        GetChatById(uint64_t iChatId);
        ChatMessage GetChatMessageById(uint64_t id);
        User        GetUserByEmail(std::string sEmail);
        Config      GetConfigById(uint64_t id);
		ActivationKey GetActivationKeyById(uint64_t id);
        bool        IsConfigExist(uint64_t id);
        void AddNewUser(const std::string& sName, const std::string& sStatus,const std::string& sPassword, const std::string sEmail, int iType);
        void CreateChat(const User& owner, const std::string& sName);
    private:
        DataBase(const std::string& sPath);
    };

} // dbapi
