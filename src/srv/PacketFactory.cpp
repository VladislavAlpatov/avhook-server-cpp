//
// Created by nullifiedvlad on 07.12.2022.
//
#include "PacketFactory.h"

#include "packets/SetUserName.h"
#include "packets/Auth.h"
#include "packets/OnlineUsersICount.h"
#include "packets/GetUserInfo.h"
#include "packets/SetUserStatus.h"
#include "packets/UpdateUserConfig.h"
#include "packets/GetUserConfigs.h"
#include "packets/SendChatMessage.h"
#include "exceptions.h"
#include "decorators/RegisteredOnly.h"
#include "packets/CreateChat.h"
#include "packets/DeleteChat.h"


// Purpose: Define packet unique ids for factory

#define PACKET_SET_USERNAME              0
#define PACKET_AUTH                      1
#define PACKET_ONLINE_USERS_COUNT        2
#define PACKET_GET_USERINFO              3
#define PACKET_SET_USER_STATUS           4
#define PACKET_UPDATE_USER_CFG           5
#define PACKET_GET_USER_CFGS             6
#define PACKET_SEND_CHAT_MESSAGE         7
#define PACKET_CREATE_CHAT               8
#define PACKET_DELETE_CHAT               9

#define MAKE_DECORATED_PACKET(dec, packetType, data) std::make_unique<dec>(std::make_unique<packetType>(data));
namespace Web
{
    using namespace Packet;

    std::unique_ptr<BasePacket> PacketFactory::Create(const nlohmann::json &data)
    {
        using namespace Packet;
        
        switch (data["type"].get<int>())
        {
            case PACKET_AUTH:                   return std::make_unique<Auth>(data);
            case PACKET_ONLINE_USERS_COUNT:     return std::make_unique<OnlineUsersICount>(data);
            case PACKET_SET_USERNAME:           return MAKE_DECORATED_PACKET(Decorator::RegisteredOnly, SetUserName,      data);
            case PACKET_GET_USERINFO:           return MAKE_DECORATED_PACKET(Decorator::RegisteredOnly, GetUserInfo,      data);
            case PACKET_SET_USER_STATUS:        return MAKE_DECORATED_PACKET(Decorator::RegisteredOnly, SetUserStatus,    data);
            case PACKET_UPDATE_USER_CFG:        return MAKE_DECORATED_PACKET(Decorator::RegisteredOnly, UpdateUserConfig, data);
            case PACKET_GET_USER_CFGS:          return MAKE_DECORATED_PACKET(Decorator::RegisteredOnly, GetUserConfigs,   data);
            case PACKET_SEND_CHAT_MESSAGE:      return MAKE_DECORATED_PACKET(Decorator::RegisteredOnly, SendChatMessage,  data);
            case PACKET_CREATE_CHAT:            return MAKE_DECORATED_PACKET(Decorator::RegisteredOnly, CreateChat,       data);
            case PACKET_DELETE_CHAT:            return MAKE_DECORATED_PACKET(Decorator::RegisteredOnly, DeleteChat,       data);
        }
        throw Exception::InvalidPacketType();

    }
} // server