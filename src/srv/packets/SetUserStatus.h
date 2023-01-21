//
// Created by nullifiedvlad on 19.12.2022.
//
#pragma once
#include "BasePacket.h"

namespace Web::Packet
{

    class SetUserStatus : public BasePacket
    {
    public:
        explicit SetUserStatus(const nlohmann::json &data);
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    private:
        std::string m_sNewUserStatus;
    };

} // packet