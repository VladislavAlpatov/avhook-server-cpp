//
// Created by Vladislav on 3/18/2023.
//

#include "ChatMembersOnly.h"
#include "../ChatRelated/ChatRelated.h"

namespace web::packet::decorator
{
    nlohmann::json ChatMembersOnly::ExecutePayload(web::ClientHandle &clientHandle)
    {
        using namespace web::packet::chat;

        const auto pPacket = GetOriginalPacket<IChatAccessible>();

        if (!pPacket->GetChat().HasUser(clientHandle.m_dbUser))
            throw std::runtime_error("You are not in this chat.");

        return m_pDecoratedPacket->ExecutePayload(clientHandle);
    }
}
