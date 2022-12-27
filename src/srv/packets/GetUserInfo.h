//
// Created by nullifiedvlad on 13.12.2022.
//
#pragma once
#include "Base.h"


namespace Web::Packet
{
    class GetUserInfo final : public Base
    {
    public:
        explicit GetUserInfo(const nlohmann::json &data);

        nlohmann::json ExecutePayload(int userId) override;
    private:
    };
} // packet