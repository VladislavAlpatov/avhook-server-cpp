//
// Created by vladislav on 07.03.23.
//

#include "GetChatList.h"
#include "../../DataBaseAPI/Chat.h"
#include "../../ClientHandle/ClientHandle.h"


namespace Web::Packet::User
{
    nlohmann::json GetChatList::ExecutePayload(ClientHandle &clientHandle)
    {
        if (clientHandle.m_dbUser != m_userFromPacket)
            throw std::runtime_error("You cant get packet list of different user");

        const auto chatList = m_userFromPacket.GetChatList();


        std::vector<nlohmann::json> jsnChatList;
        jsnChatList.reserve(chatList.size());


        for (const auto& chat : chatList)
            jsnChatList.push_back({{"id", chat.GetID()}});

        return {{"chats", jsnChatList}};
    }
}