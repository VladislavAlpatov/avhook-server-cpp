//
// Created by nullifiedvlad on 07.12.2022.
//
#pragma once
#include "packets/BasePacket.h"
#include "decorators/BaseDecorator.h"


#include <memory>

namespace Web
{
    class PacketFactory final
    {
	public:
        static std::unique_ptr<Packet::BasePacket> Create(const nlohmann::json& data);
    };

} // server