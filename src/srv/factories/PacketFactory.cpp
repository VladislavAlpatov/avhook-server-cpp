//
// Created by nullifiedvlad on 07.12.2022.
//
// Purpose: Create Packet based on JSON data.
//
#include "PacketFactory.h"

// User
#include "../packets/UserRelated/GetName.h"
#include "../packets/UserRelated/GetStatus.h"
#include "../packets/UserRelated/GetChatList.h"
#include "../packets/UserRelated/SetName.h"
#include "../packets/UserRelated/SetStatus.h"
#include "../packets/UserRelated/GetConfigs.h"
#include "../packets/UserRelated/GetSubscriptions.h"

// Chat
#include "../packets/ChatRelated/GetName.h"
#include "../packets/ChatRelated/SendMessage.h"
#include "../packets/ChatRelated/GetInvite.h"
#include "../packets/ChatRelated/GetHistory.h"

// Chat message
#include "../packets/ChatMessageRelated/GetText.h"
#include "../packets/ChatMessageRelated/GetOwner.h"

// Config
#include "../packets/ConfigRelated/GetData.h"

// Subscription
#include "../packets/Subscription/GetExpireDate.h"
#include "../packets/Subscription/CheckExpiration.h"

// Product
#include "../packets/ProductRelated/GetName.h"

// Misc
#include "../packets/Misc/Auth.h"

#include "../packets/decorators/RegisteredOnly.h"
#include "../packets/decorators/OwnerOnly.h"
#include "../packets/decorators/ChatMembersOnly.h"


#include <functional>

#include "../exceptions.h"

using namespace Web;
using namespace Web::Packet;
using namespace Web::Packet::Decorator;

static std::map<std::string,  std::function<std::unique_ptr<IPayloadExecutable>(const nlohmann::json&)>> packetRoutMap
        {
                // ==================
                // User related packets
                // ==================
                {"/user/get/name",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new User::GetName(data), new RegisteredOnly());}},

                {"/user/get/status",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new User::GetStatus(data), new RegisteredOnly());}},

                {"/user/get/chat_list",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new User::GetChatList(data), new RegisteredOnly());}},

                {"/user/get/configs",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new User::GetConfigs(data), new RegisteredOnly());}},


				{"/user/get/subscriptions",[](const nlohmann::json& data) -> auto
				{ return MultipleDecoration(new User::GetSubscriptions(data), new RegisteredOnly());}},

                {"/user/set/name",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new User::SetName(data), new RegisteredOnly(), new OwnerOnly());}},

                {"/user/set/status",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new User::SetStatus(data), new RegisteredOnly(), new OwnerOnly());}},

                // ==================
                // Chat related packets
                // ==================
                {"/chat/get/name",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new Chat::GetName(data), new RegisteredOnly(), new ChatMembersOnly());}},

                {"/chat/get/invite",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new Chat::GetInvite(data), new RegisteredOnly(), new ChatMembersOnly());}},

                {"/chat/get/history",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new Chat::GetHistory(data), new RegisteredOnly(), new ChatMembersOnly());}},

                {"/chat/send/message",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new Chat::SendMessage(data), new RegisteredOnly(), new ChatMembersOnly());}},

                // ==================
                // Chat message related packets
                // ==================
                {"/chat/message/text",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new ChatMessage::GetText(data), new RegisteredOnly());}},

                {"/chat/message/owner",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new ChatMessage::GetOwner(data), new RegisteredOnly(),
						new ChatMembersOnly());}},

                {"/config/get/data",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new Config::GetData(data), new RegisteredOnly(), new OwnerOnly());}},

				// ==================
				// Subscription packets
				// ==================
				{"/subscription/get/expire_date",[](const nlohmann::json& data) -> auto
				{ return MultipleDecoration(new Subscription::GetExpireDate(data), new RegisteredOnly(), new OwnerOnly());}},

				{"/subscription/get/expiration_status",[](const nlohmann::json& data) -> auto
				{ return MultipleDecoration(new Subscription::CheckExpiration(data), new RegisteredOnly(), new OwnerOnly());}},

				// ==================
				// Product packets
				// ==================
				{"/product/get/name",[](const nlohmann::json& data) -> auto
				{ return MultipleDecoration(new Product::GetName(data));}},


                // ==================
                // Misc packets
                // ==================
                {"/auth",[](const nlohmann::json& data) -> auto
                {return MultipleDecoration(new Misc::Auth(data));}},
        };

namespace Web
{

    std::unique_ptr<IPayloadExecutable> PacketFactory::Create(const nlohmann::json &data)
    {
        if (!data.contains("route"))
            throw std::runtime_error("\"route\" filed seems does not exist");


        const std::string route = data["route"];

        if (!packetRoutMap.contains(route))
            throw Exception::InvalidPacketType();

        return packetRoutMap[route](data);

    }
} // server