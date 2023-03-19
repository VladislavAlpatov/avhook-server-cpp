//
// Created by nullifiedvlad on 07.12.2022.
//
// Purpose: Create Packet based on JSON data.
//
#include "PacketFactory.h"


#include "../packets/UserRelated/GetName.h"
#include "../packets/UserRelated/GetStatus.h"
#include "../packets/UserRelated/GetChatList.h"
#include "../packets/UserRelated/SetName.h"


#include "../packets/ChatRelated/GetName.h"
#include "../packets/ChatRelated/SendMessage.h"
#include "../packets/ChatRelated/GetInvite.h"


#include "../packets/Misc/Auth.h"

#include "../packets/decorators/RegisteredOnly.h"
#include "../packets/decorators/CantModifyOtherUsers.h"
#include "../packets/decorators/ChatMembersOnly.h"


#include <functional>

#include "../exceptions.h"

using namespace Web;
using namespace Web::Packet;
using namespace Web::Packet::Decorator;

static std::map<std::string,  std::function<std::unique_ptr<BasePacket>(const nlohmann::json&)>> packetRoutMap
        {
                // ==================
                // User related packets
                // ==================
                {"/user/get/name",[](const nlohmann::json& data) -> auto
                { return MutipleDecoration(new User::GetName(data), new RegisteredOnly());}},

                {"/user/get/status",[](const nlohmann::json& data) -> auto
                { return MutipleDecoration(new User::GetStatus(data), new RegisteredOnly());}},

                {"/user/get/chat_list",[](const nlohmann::json& data) -> auto
                { return MutipleDecoration(new User::GetChatList(data), new RegisteredOnly());}},

                {"/user/set/name",[](const nlohmann::json& data) -> auto
                { return MutipleDecoration(new User::SetName(data), new RegisteredOnly(), new CantModifyOtherUsers());}},

                // ==================
                // Chat related packets
                // ==================
                {"/chat/get/name",[](const nlohmann::json& data) -> auto
                { return MutipleDecoration(new Chat::GetName(data), new RegisteredOnly(), new ChatMembersOnly());}},

                {"/chat/get/invite",[](const nlohmann::json& data) -> auto
                { return MutipleDecoration(new Chat::GetInvite(data), new RegisteredOnly(), new ChatMembersOnly());}},

                {"/chat/send/message",[](const nlohmann::json& data) -> auto
                { return MutipleDecoration(new Chat::SendMessage(data), new RegisteredOnly(), new ChatMembersOnly());}},

                // ==================
                // Misc packets
                // ==================
                {"/auth",[](const nlohmann::json& data) -> auto
                { return MutipleDecoration(new Misc::Auth(data));}},
        };

namespace Web
{

    std::unique_ptr<BasePacket> PacketFactory::Create(const nlohmann::json &data)
    {

        if (!data.contains("route"))
            throw std::runtime_error("\"route\" filed seems does not exist");


        const std::string route = data["route"];

        if (!packetRoutMap.contains(route))
            throw Exception::InvalidPacketType();

        return packetRoutMap[route](data);

    }
} // server