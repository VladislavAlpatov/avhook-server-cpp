//
// Created by nullifiedvlad on 19.12.2022.
//
#pragma once
#include "Base.h"

namespace Web::Packet
{

    class SetUserStatus : public Base
    {
    public:
        explicit SetUserStatus(const nlohmann::json &data);
        nlohmann::json ExecutePayload(int userId) override;
    private:
        std::string m_sNewUserStatus;
    };

} // packet