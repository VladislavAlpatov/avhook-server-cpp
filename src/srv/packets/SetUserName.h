//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include "Base.h"


namespace server::packet
{
    class SetUserName : public Base
    {
    public:
        explicit SetUserName(const nlohmann::json& data);
        std::string execute_payload(int userId) override;
    private:
        std::string m_sNewUserName;

        static bool is_username_valid(const std::string& name);
    };
} // packet