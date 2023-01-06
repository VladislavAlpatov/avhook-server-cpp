//
// Created by nullifiedvlad on 19.12.2022.
//
#pragma once
#include "BasePacket.h"
namespace Web::Packet
{

    class UpdateAVhookUserConfig : public BasePacket
    {
    public:
        explicit UpdateAVhookUserConfig(const nlohmann::json &data);

        nlohmann::json ExecutePayload(int userId) override;

    private:
        int m_iConfigId;
        nlohmann::json m_jsonConfig;
    };

} //