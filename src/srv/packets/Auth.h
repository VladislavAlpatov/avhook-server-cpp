//
// Created by nullifiedvlad on 08.12.2022.
//
#pragma once
#include "Base.h"


namespace Web::packet
{

    class Auth final : public Base
    {
    public:
        explicit Auth(const nlohmann::json &data);
        std::string execute_payload(int userId) override;
    private:
        std::string m_sUserPasswordHash;
        std::string m_sUserEmail;
    };

} // packet