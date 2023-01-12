//
// Created by Vlad on 1/5/2023.
//

#include "SendChatMessage.h"

namespace Web::Packet
{

    SendChatMessage::SendChatMessage(const nlohmann::json &data) : BasePacket(data)
    {

    }
} // Packets
