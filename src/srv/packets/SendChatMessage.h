//
// Created by Vlad on 1/5/2023.
//
#pragma once
#include "BasePacket.h"
#include "BasePacket.h"


namespace Web::Packet
{
    class SendChatMessage : public BasePacket
    {
    public:
        explicit SendChatMessage(const nlohmann::json &data);

    };


} // Packets
