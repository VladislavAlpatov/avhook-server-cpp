//
// Created by Vladislav on 3/18/2023.
//

#pragma once
#include "../BasePacket.h"
#include "../../DataBaseAPI/Chat.h"
#include "../interfaces/IChatAccessible.h"

namespace Web::Packet::Decorator
{
    class ChatMembersOnly;
}

namespace Web::Packet::Chat
{
    class ChatRelated : public BasePacket, public IChatAccessible
    {
        friend Web::Packet::Decorator::ChatMembersOnly;
    public:
        explicit ChatRelated(const nlohmann::json &data);

        DBAPI::Chat GetChat() override;

    protected:
        DBAPI::Chat m_chatFromPacket;
    };
}
