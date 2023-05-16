//
// Created by Vladislav on 3/18/2023.
//

#pragma once
#include "../BasePacket.h"
#include "../../DataBaseAPI/Chat.h"
#include "../interfaces/IChatAccessible.h"

namespace web::packet::decorator
{
    class ChatMembersOnly;
}

namespace web::packet::chat
{
    class ChatRelated : public BasePacket, public IChatAccessible
    {
        friend web::packet::decorator::ChatMembersOnly;
    public:
        explicit ChatRelated(const nlohmann::json &data);

        dbapi::Chat GetChat() override;

    protected:
        dbapi::Chat m_chatFromPacket;
    };
}
