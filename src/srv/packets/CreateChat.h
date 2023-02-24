//
// Created by Vlad on 12.01.2023.
//

#pragma once
#include "BasePacket.h"
namespace Web::Packet
{
    class CreateChat final : public BasePacket
    {
    public:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
        explicit CreateChat(const nlohmann::json &data);
        std::string m_sChatName;
    };
} // Packet
