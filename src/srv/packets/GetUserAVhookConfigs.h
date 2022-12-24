//
// Created by nullifiedvlad on 20.12.2022.
//
#pragma once
#include "Base.h"
namespace Web::packet
{

    class GetUserAVhookConfigs final : public Base
    {
    public:
        explicit GetUserAVhookConfigs(const nlohmann::json &data);

        std::string execute_payload(int userId) override;

    };

} // packet