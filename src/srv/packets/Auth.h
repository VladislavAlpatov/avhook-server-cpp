//
// Created by nullifiedvlad on 08.12.2022.
//
#pragma once
#include "Base.h"


namespace Web::Packet
{

    class Auth final : public Base
    {
    public:
        explicit Auth(const nlohmann::json &data);
        nlohmann::json ExecutePayload(int userId) override;
    private:
        std::string m_sUserPasswordHash;
        std::string m_sUserEmail;
    };

} // packet