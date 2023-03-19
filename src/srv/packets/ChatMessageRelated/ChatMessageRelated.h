//
// Created by Vladislav on 3/19/2023.
//

#pragma once
#include "../BasePacket.h"
#include "../../DataBaseAPI/ChatMessage.h"


namespace Web::Packet::ChatMessage
{
    class ChatMessageRelated : public BasePacket
    {
    public:
        explicit ChatMessageRelated(const nlohmann::json &data);
    private:
        DBAPI::ChatMessage m_messageFromPacket;
    };

}