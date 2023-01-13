//
// Created by Vlad on 1/5/2023.
//
#pragma once
#include "BasePacket.h"
namespace Web::Packet
{
    class SendChatMessage : public BasePacket
    {
    public:
        explicit SendChatMessage(const nlohmann::json &data);

        nlohmann::json ExecutePayload(int userId) override;
    private:
        std::string m_sText;
        int m_iChatId;
    };


} // Packets
