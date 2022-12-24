//
// Created by nullifiedvlad on 07.12.2022.
//
#include "PacketFactory.h"

#include "packets/SetUserName.h"
#include "packets/Auth.h"
#include "packets/OnlineUsersICount.h"
#include "packets/GetUserInfo.h"
#include "packets/SetUserStatus.h"
#include "packets/UpdateAVhookUserConfig.h"
#include "packets/GetUserAVhookConfigs.h"
#include "exceptions.h"

#define PACKET_SET_USERNAME              0
#define PACKET_AUTH                      1
#define PACKET_ONLINE_USERS_COUNT        2
#define PACKET_GET_USERINFO              3
#define PACKET_SET_USER_STATUS           4
#define PACKET_UPDATE_USER_AVHOOK_CFG    5
#define PACKET_GET_USER_AVHOOK_CFGS      6


namespace Web
{
    std::shared_ptr<packet::Base> PacketFactory::create(const nlohmann::json &data)
    {
        switch (data["type"].get<int>())
        {
            case PACKET_SET_USERNAME:           return std::make_shared<packet::SetUserName>(data);
            case PACKET_AUTH:                   return std::make_shared<packet::Auth>(data);
            case PACKET_ONLINE_USERS_COUNT:     return std::make_shared<packet::OnlineUsersICount>(data);
            case PACKET_GET_USERINFO:           return std::make_shared<packet::GetUserInfo>(data);
            case PACKET_SET_USER_STATUS:        return std::make_shared<packet::SetUserStatus>(data);
            case PACKET_UPDATE_USER_AVHOOK_CFG: return std::make_shared<packet::UpdateAVhookUserConfig>(data);
            case PACKET_GET_USER_AVHOOK_CFGS:   return std::make_shared<packet::GetUserAVhookConfigs>(data);
        }
        throw exception::InvalidPacketType();

    }
} // server