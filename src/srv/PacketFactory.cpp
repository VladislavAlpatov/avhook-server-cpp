//
// Created by nullifiedvlad on 07.12.2022.
//
#include "PacketFactory.h"

#include "packets/SetUserName.h"
#include "packets/Auth.h"
#include "packets/OnlineUsersICount.h"
#include "packets/GetUserInfo.h"
#include "packets/SetUserStatus.h"
#include "exceptions.h"

#define PACKET_SET_USERNAME       0
#define PACKET_AUTH               1
#define PACKET_ONLINE_USERS_COUNT 2
#define PACKET_GET_USERINFO       3
#define PACKET_SET_USER_STATUS    4

namespace server
{
    std::shared_ptr<packet::Base> PacketFactory::create(const nlohmann::json &data)
    {
        switch (data["type"].get<int>())
        {
            case PACKET_SET_USERNAME:       return std::make_shared<packet::SetUserName>(data);
            case PACKET_AUTH:               return std::make_shared<packet::Auth>(data);
            case PACKET_ONLINE_USERS_COUNT: return std::make_shared<packet::OnlineUsersICount>(data);
            case PACKET_GET_USERINFO:       return std::make_shared<packet::GetUserInfo>(data);
            case PACKET_SET_USER_STATUS:    return std::make_shared<packet::SetUserStatus>(data);

        }
        throw exception::InvalidPacketType();

    }
} // server