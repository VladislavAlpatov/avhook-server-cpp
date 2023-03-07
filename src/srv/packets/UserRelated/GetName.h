//
// Created by vladislav on 07.03.23.
//

#pragma once
#include "../BasePacket.h"


namespace Web::Packet::User
{
    class GetName final : public BasePacket
    {
    public:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
        explicit GetName(const nlohmann::json &data);
    private:
        int m_iUserId = 0;
    };
} // User
