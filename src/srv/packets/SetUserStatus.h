//
// Created by nullifiedvlad on 19.12.2022.
//
#pragma once
#include "Base.h"

namespace server::packet
{

    class SetUserStatus : public Base
    {
    public:
        explicit SetUserStatus(const nlohmann::json &data);
        std::string execute_payload(int userId) override;
    private:
        std::string m_sNewUserStatus;
    };

} // packet