//
// Created by nullifiedvlad on 13.12.2022.
//
#pragma once
#include "Base.h"


namespace Web::packet
{
    class GetUserInfo final : public Base
    {
    public:
        explicit GetUserInfo(const nlohmann::json &data);

        std::string execute_payload(int userId) override;
    private:
    };
} // packet