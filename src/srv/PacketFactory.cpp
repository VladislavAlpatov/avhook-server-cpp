//
// Created by nullifiedvlad on 07.12.2022.
//
#include "PacketFactory.h"
#include "packets/SetUserName.h"
#include "exceptions.h"
namespace server
{
    std::shared_ptr<packet::Base> PacketFactory::create(const nlohmann::json &data, sql::Connection *pConn)
    {

        switch (data["type"].get<int>())
        {
            case PACKET_SETUSERNAME:
                return std::make_shared<packet::SetUserName>(data, pConn);
        }
        throw exception::InvalidPacketType();

    }
} // server