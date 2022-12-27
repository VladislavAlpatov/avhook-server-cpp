//
// Created by nullifiedvlad on 20.12.2022.
//
#pragma once
#include "Base.h"
namespace Web::Packet
{

    class GetUserAVhookConfigs final : public Base
    {
    public:
        explicit GetUserAVhookConfigs(const nlohmann::json &data);

        nlohmann::json ExecutePayload(int userId) override;

    };

} // packet