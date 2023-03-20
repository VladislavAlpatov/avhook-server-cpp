//
// Created by nullifiedvlad on 07.12.2022.
//
#pragma once
#include "../packets/IPayloadExecutable.h"
#include <memory>

namespace Web
{
    class PacketFactory final
    {
	public:
        static std::unique_ptr<IPayloadExecutable> Create(const nlohmann::json& data);
    };

} // server