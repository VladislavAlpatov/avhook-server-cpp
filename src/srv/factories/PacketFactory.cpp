//
// Created by nullifiedvlad on 07.12.2022.
//
// Purpose: Create packet based on JSON data.
//
#include "PacketFactory.h"

// User
#include "../packets/User/GetName.h"
#include "../packets/User/GetStatus.h"
#include "../packets/User/GetChatList.h"
#include "../packets/User/SetName.h"
#include "../packets/User/SetStatus.h"
#include "../packets/User/GetConfigs.h"
#include "../packets/User/GetSubscriptions.h"

// chat
#include "../packets/chat/GetName.h"
#include "../packets/chat/SendMessage.h"
#include "../packets/chat/GetInvite.h"
#include "../packets/chat/GetHistory.h"

// chat message
#include "../packets/ChatMessageRelated/GetText.h"
#include "../packets/ChatMessageRelated/GetOwner.h"

// config
#include "../packets/config/GetData.h"

// subscription
#include "../packets/Subscription/GetExpireDate.h"
#include "../packets/Subscription/CheckExpiration.h"
#include "../packets/Subscription/GetProduct.h"

// Product
#include "../packets/ProductRelated/GetName.h"
#include "../packets/ProductRelated/GetProductList.h"

// Misc
#include "../packets/Misc/Auth.h"

#include "../packets/decorators/RegisteredOnly.h"
#include "../packets/decorators/OwnerOnly.h"
#include "../packets/decorators/ChatMembersOnly.h"


#include <functional>

#include "../exceptions.h"

using namespace web;
using namespace web::packet;
using namespace web::packet::decorator;

static std::map<std::string,  std::function<std::unique_ptr<IPayloadExecutable>(const nlohmann::json&)>> packetRoutMap
        {
                // ==================
                // User related packets
                // ==================
                {"/user/get/name",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new user::GetName(data), new RegisteredOnly());}},

                {"/user/get/status",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new user::GetStatus(data), new RegisteredOnly());}},

                {"/user/get/chat_list",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new user::GetChatList(data), new RegisteredOnly());}},

                {"/user/get/configs",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new user::GetConfigs(data), new RegisteredOnly());}},


				{"/user/get/subscriptions",[](const nlohmann::json& data) -> auto
				{ return MultipleDecoration(new user::GetSubscriptions(data), new RegisteredOnly());}},

                {"/user/set/name",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new user::SetName(data), new RegisteredOnly(), new OwnerOnly());}},

                {"/user/set/status",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new user::SetStatus(data), new RegisteredOnly(), new OwnerOnly());}},

                // ==================
                // chat related packets
                // ==================
                {"/chat/get/name",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new chat::GetName(data), new RegisteredOnly(), new ChatMembersOnly());}},

                {"/chat/get/invite",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new chat::GetInvite(data), new RegisteredOnly(), new ChatMembersOnly());}},

                {"/chat/get/history",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new chat::GetHistory(data), new RegisteredOnly(), new ChatMembersOnly());}},

                {"/chat/send/message",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new chat::SendMessage(data), new RegisteredOnly(), new ChatMembersOnly());}},

                // ==================
                // chat message related packets
                // ==================
                {"/chat/message/text",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new message::GetText(data), new RegisteredOnly());}},

                {"/chat/message/owner",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new message::GetOwner(data), new RegisteredOnly(),
						new ChatMembersOnly());}},

                {"/config/get/data",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new config::GetData(data), new RegisteredOnly(), new OwnerOnly());}},

				// ==================
				// subscription packets
				// ==================
				{"/subscription/get/expire_date",[](const nlohmann::json& data) -> auto
				{ return MultipleDecoration(new subscription::GetExpireDate(data), new RegisteredOnly(), new OwnerOnly());}},

				{"/subscription/get/expiration_status",[](const nlohmann::json& data) -> auto
				{ return MultipleDecoration(new subscription::CheckExpiration(data), new RegisteredOnly(), new OwnerOnly());}},

                {"/subscription/get/product",[](const nlohmann::json& data) -> auto
                { return MultipleDecoration(new subscription::GetProduct(data), new RegisteredOnly(), new OwnerOnly());}},

				// ==================
				// Product packets
				// ==================
				{"/product/get/name",[](const nlohmann::json& data) -> auto
				{ return MultipleDecoration(new Product::GetName(data));}},

				{"/product/get/all",[](const nlohmann::json& data) -> auto
				{ return MultipleDecoration(new Product::GetProductList(data));}},

                // ==================
                // Misc packets
                // ==================
                {"/auth",[](const nlohmann::json& data) -> auto
                {return MultipleDecoration(new Misc::Auth(data));}},
        };

namespace web
{

    std::unique_ptr<IPayloadExecutable> PacketFactory::Create(const nlohmann::json &data)
    {
        if (!data.contains("route"))
            throw std::runtime_error("\"route\" filed seems does not exist");


        const auto& route = data["route"];

        if (!packetRoutMap.contains(route))
            throw Exception::InvalidPacketType();

        return packetRoutMap[route](data);

    }
} // server