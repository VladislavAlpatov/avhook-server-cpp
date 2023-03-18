//
// Created by Vladislav on 3/18/2023.
//

#pragma once
#include "../BasePacket.h"
#include "../../DataBaseAPI/Chat.h"

namespace Web::Packet::Decorator
{
    class ChatMembersOnly;
}

namespace Web::Packet::Chat
{
    class ChatRelated : public BasePacket
    {
        friend Web::Packet::Decorator::ChatMembersOnly;
    public:
        explicit ChatRelated(const nlohmann::json &data);

    protected:
        DBAPI::Chat m_chatFromPacket;
    };
}
