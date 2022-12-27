//
// Created by nullifiedvlad on 07.12.2022.
//
#pragma once
#include "packets/Base.h"
#include <memory>

namespace Web
{
    class PacketFactory final
    {
	public:
        static std::shared_ptr<Packet::Base> Create(const nlohmann::json& data);
    };

} // server