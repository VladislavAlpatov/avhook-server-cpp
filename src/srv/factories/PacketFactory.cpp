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

#include "../packets/Misc/Auth.h"
#include "../packets/PacketID.h"

#include "../packets/decorators/RegisteredOnly.h"


#include "../exceptions.h"


namespace Web
{
    using namespace Packet;
    using namespace Decorator;


    std::unique_ptr<BasePacket> PacketFactory::Create(const nlohmann::json &data)
    {
        switch (data["type"].get<int>())
        {
            // Put User related packets here:
            case PacketID::UserGetName:         return MutipleDecoration(new Packet::User::GetName(data),     new RegisteredOnly());
            case PacketID::UserGetChatList:     return MutipleDecoration(new Packet::User::GetChatList(data), new RegisteredOnly());
            case PacketID::UserGetStatus:       return MutipleDecoration(new Packet::User::GetStatus(data),   new RegisteredOnly());
            case PacketID::UserSetName:         return MutipleDecoration(new Packet::User::SetName(data),     new RegisteredOnly());


            // Put Misc related packets here:
            case PacketID::Auth:                return MutipleDecoration(new Packet::Auth(data));
        }
        throw Exception::InvalidPacketType();

    }
} // server