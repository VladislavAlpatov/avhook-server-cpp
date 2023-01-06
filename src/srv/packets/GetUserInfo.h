//
// Created by nullifiedvlad on 13.12.2022.
//
#pragma once
#include "BasePacket.h"


namespace Web::Packet
{
    class GetUserInfo final : public BasePacket
    {
    public:
        explicit GetUserInfo(const nlohmann::json &data);

        nlohmann::json ExecutePayload(int userId) override;
    private:
    };
} // packet