//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include "BasePacket.h"


namespace Web::Packet
{
    class SetUserName : public BasePacket
    {
    public:
        explicit SetUserName(const nlohmann::json& data);
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    private:
        std::string m_sNewUserName;

        static bool IsUsernameValid(const std::string& name);
    };
} // packet