//
// Created by Vladislav on 3/19/2023.
//

#pragma once
#include "../BasePacket.h"
#include "../../DataBaseAPI/ChatMessage.h"
#include "../IChatAccessible.h"

namespace Web::Packet::ChatMessage
{
    class ChatMessageRelated : public BasePacket, public IChatAccessible
    {
    public:
        DBAPI::Chat GetChat() override;

        explicit ChatMessageRelated(const nlohmann::json &data);

    protected:
        DBAPI::ChatMessage m_messageFromPacket;
    };

}
