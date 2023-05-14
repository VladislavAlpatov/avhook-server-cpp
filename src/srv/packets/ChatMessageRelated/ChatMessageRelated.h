//
// Created by Vladislav on 3/19/2023.
//

#pragma once
#include "../BasePacket.h"
#include "../../DataBaseAPI/ChatMessage.h"
#include "../interfaces/IChatAccessible.h"

namespace web::packet::message
{
    class ChatMessageRelated : public BasePacket, public IChatAccessible
    {
    public:
        dbapi::Chat GetChat() override;

        explicit ChatMessageRelated(const nlohmann::json &data);

    protected:
        dbapi::ChatMessage m_messageFromPacket;
    };

}
