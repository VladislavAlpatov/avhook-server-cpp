//
// Created by nullifiedvlad on 07.12.2022.
//
// Purpose: Create Packet based on JSON data.
//
#include "PacketFactory.h"

#include "../packets/UserRelated/GetName.h"

#include "../packets/decorators/RegisteredOnly.h"

#include "../packets/PacketID.h"

#include "../exceptions.h"


namespace Web
{
    using namespace Packet;
    using namespace Decorator;

    
    std::unique_ptr<BasePacket> PacketFactory::Create(const nlohmann::json &data)
    {

        switch (data["type"].get<int>())
        {
            case PacketID::UserGetName:         return std::make_unique<Packet::User::GetName>(data);
        }
        throw Exception::InvalidPacketType();

    }
} // server