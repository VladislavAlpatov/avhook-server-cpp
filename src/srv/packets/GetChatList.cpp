#include "GetChatList.h"
#include "../ClientHandle/ClientHandle.h"
#include "../DataBaseAPI/Chat.h"

#include <vector>


namespace Web::Packet
{

    GetChatList::GetChatList(const nlohmann::json &data) : BasePacket(data)
    {

    }

    nlohmann::json GetChatList::ExecutePayload(ClientHandle &clientHandle)
    {
        std::vector<nlohmann::json> jsnChats;
        const auto chats = clientHandle.m_dbUser.GetChatList();
        jsnChats.reserve(chats.size());

        for (const auto& chat : chats)
            jsnChats.push_back({
                    {"name", chat.GetName()},
                    {"id", chat.GetID()},
                    {"invite", chat.GetInviteLink()}
            });

        return {{"chats", jsnChats}};
    }
}