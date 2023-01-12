//
// Created by nullifiedvlad on 20.12.2022.
//
#pragma once
#include "BasePacket.h"
namespace Web::Packet
{

    class GetUserConfigs final : public BasePacket
    {
    public:
        explicit GetUserConfigs(const nlohmann::json &data);

        nlohmann::json ExecutePayload(int userId) override;

    };

} // packet