//
// Created by Vlad on 12.01.2023.
//

#pragma once
#include "BasePacket.h"
namespace Web::Packet
{
    class CreateChat : public BasePacket
    {
    public:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;

    public:
        explicit CreateChat(const nlohmann::json &data);
        std::string m_sChatName;
        static size_t CreateChatPublicId() ;
    };
} // Packet
