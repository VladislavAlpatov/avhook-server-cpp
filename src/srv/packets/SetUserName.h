//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include "Base.h"


namespace Web::Packet
{
    class SetUserName : public Base
    {
    public:
        explicit SetUserName(const nlohmann::json& data);
        nlohmann::json ExecutePayload(int userId) override;
    private:
        std::string m_sNewUserName;

        static bool IsUsernameValid(const std::string& name);
    };
} // packet