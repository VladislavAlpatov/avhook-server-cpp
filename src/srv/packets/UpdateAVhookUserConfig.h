//
// Created by nullifiedvlad on 19.12.2022.
//
#pragma once
#include "Base.h"
namespace server::packet
{

    class UpdateAVhookUserConfig : public Base
    {
    public:
        explicit UpdateAVhookUserConfig(const nlohmann::json &data);

        std::string execute_payload(int userId) override;

    private:
        int m_iConfigId;
        nlohmann::json m_jsonConfig;
    };

} //