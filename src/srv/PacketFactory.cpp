//
// Created by nullifiedvlad on 07.12.2022.
//
#include "PacketFactory.h"
#include "packets/SetUserName.h"
#include "packets/Auth.h"
#include "packets/OnlineUsersICount.h"

#include "../lib/sqlite/connection.h"
#include "exceptions.h"


namespace server
{
    std::shared_ptr<packet::Base> PacketFactory::create(const nlohmann::json &data)
    {
        switch (data["type"].get<int>())
        {
            case PACKET_SETUSERNAME:      return std::make_shared<packet::SetUserName>(data);
            case PACKET_AUTH:             return std::make_shared<packet::Auth>(data);
            case PACKET_ONLINEUSERSCOUNT: return std::make_shared<packet::OnlineUsersICount>(data);
        }
        throw exception::InvalidPacketType();

    }
} // server