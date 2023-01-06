//
// Created by nullifiedvlad on 20.12.2022.
//
#pragma once
#include "BasePacket.h"
namespace Web::Packet
{

    class GetUserAVhookConfigs final : public BasePacket
    {
    public:
        explicit GetUserAVhookConfigs(const nlohmann::json &data);

        nlohmann::json ExecutePayload(int userId) override;

    };

} // packet