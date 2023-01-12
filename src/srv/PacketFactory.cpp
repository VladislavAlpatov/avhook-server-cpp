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
#include "exceptions.h"

// Purpose: Define packet unique ids for factory

#define PACKET_SET_USERNAME              0
#define PACKET_AUTH                      1
#define PACKET_ONLINE_USERS_COUNT        2
#define PACKET_GET_USERINFO              3
#define PACKET_SET_USER_STATUS           4
#define PACKET_UPDATE_USER_AVHOOK_CFG    5
#define PACKET_GET_USER_AVHOOK_CFGS      6
#define PACKET_SEND_CHAT_MESSAGE         7


namespace Web
{
    std::shared_ptr<Packet::BasePacket> PacketFactory::Create(const nlohmann::json &data)
    {
        switch (data["type"].get<int>())
        {
            case PACKET_SET_USERNAME:           return std::make_shared<Packet::SetUserName>(data);
            case PACKET_AUTH:                   return std::make_shared<Packet::Auth>(data);
            case PACKET_ONLINE_USERS_COUNT:     return std::make_shared<Packet::OnlineUsersICount>(data);
            case PACKET_GET_USERINFO:           return std::make_shared<Packet::GetUserInfo>(data);
            case PACKET_SET_USER_STATUS:        return std::make_shared<Packet::SetUserStatus>(data);
            case PACKET_UPDATE_USER_AVHOOK_CFG: return std::make_shared<Packet::UpdateUserConfig>(data);
            case PACKET_GET_USER_AVHOOK_CFGS:   return std::make_shared<Packet::GetUserConfigs>(data);
        }
        throw Exception::InvalidPacketType();

    }
} // server