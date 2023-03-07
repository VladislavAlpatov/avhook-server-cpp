//
// Created by nullifiedvlad on 07.12.2022.
//
// Purpose: Create Packet based on JSON data.
//
#include "PacketFactory.h"

#include "../packets/SetUserName.h"
#include "../packets/Auth.h"
#include "../packets/OnlineUsersICount.h"
#include "../packets/GetUserInfo.h"
#include "../packets/SetUserStatus.h"
#include "../packets/UpdateUserConfig.h"
#include "../packets/GetUserConfigs.h"
#include "../packets/SendChatMessage.h"
#include "../decorators/RegisteredOnly.h"
#include "../packets/CreateChat.h"
#include "../packets/DeleteChat.h"
#include "../packets/DownloadFile.h"
#include "../packets/GetChatList.h"

#include "../exceptions.h"

// Unique ids of each packet

#define PACKET_SET_USERNAME              0
#define PACKET_AUTH                      1
#define PACKET_ONLINE_USERS_COUNT        2
#define PACKET_GET_USERINFO              3
#define PACKET_SET_USER_STATUS           4
#define PACKET_UPDATE_USER_CFG           5
#define PACKET_GET_USER_CONFIGS          6
#define PACKET_SEND_CHAT_MESSAGE         7
#define PACKET_CREATE_CHAT               8
#define PACKET_DELETE_CHAT               9
#define PACKET_DOWNLOAD_FILE             10
#define PACKET_GET_CHAT_LIST             11


namespace Web
{
    using namespace Packet;
    using namespace Decorator;
    std::unique_ptr<BasePacket> PacketFactory::Create(const nlohmann::json &data)
    {

        switch (data["type"].get<int>())
        {
            case PACKET_AUTH:                   return std::make_unique<Auth>(data);
            case PACKET_ONLINE_USERS_COUNT:     return MutipleDecoration(new OnlineUsersICount(data), new RegisteredOnly());
            case PACKET_SET_USERNAME:           return MutipleDecoration(new SetUserName(data), new RegisteredOnly());
            case PACKET_GET_USERINFO:           return MutipleDecoration(new GetUserInfo(data),   new RegisteredOnly());
            case PACKET_SET_USER_STATUS:        return MutipleDecoration(new SetUserStatus(data), new RegisteredOnly());
            case PACKET_UPDATE_USER_CFG:        return MutipleDecoration(new UpdateUserConfig(data), new RegisteredOnly());
            case PACKET_GET_USER_CONFIGS:       return MutipleDecoration(new GetUserConfigs(data), new RegisteredOnly());
            case PACKET_SEND_CHAT_MESSAGE:      return MutipleDecoration(new SendChatMessage(data), new RegisteredOnly());
            case PACKET_CREATE_CHAT:            return MutipleDecoration(new CreateChat(data), new RegisteredOnly());
            case PACKET_DELETE_CHAT:            return MutipleDecoration(new DeleteChat(data), new RegisteredOnly());
            case PACKET_DOWNLOAD_FILE:          return MutipleDecoration(new DownloadFile(data), new RegisteredOnly());
            case PACKET_GET_CHAT_LIST:          return MutipleDecoration(new GetChatList(data), new RegisteredOnly());
        }
        throw Exception::InvalidPacketType();

    }
} // server