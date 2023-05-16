//
// Created by vladislav on 07.03.23.
//

#include "GetChatList.h"
#include "../../DataBaseAPI/Chat.h"
#include "../../ClientHandle/ClientHandle.h"


namespace web::packet::user
{
    nlohmann::json GetChatList::ExecutePayload(ClientHandle &clientHandle)
    {
        const auto chatList = m_pUserFromPacket.GetChatList();


        std::vector<nlohmann::json> jsnChatList;
        jsnChatList.reserve(chatList.size());


        for (const auto& chat : chatList)
            jsnChatList.push_back({{"id", chat.GetID()}});

        return {{"chats", jsnChatList}};
    }
}