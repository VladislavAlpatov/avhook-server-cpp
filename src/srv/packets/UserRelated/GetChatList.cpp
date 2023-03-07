//
// Created by vladislav on 07.03.23.
//

#include "GetChatList.h"

#include "../../DataBaseAPI/DataBase.h"
#include "../../DataBaseAPI/User.h"
#include "../../DataBaseAPI/Chat.h"


#include "../exceptions.h"



namespace Web::Packet::User
{

    GetChatList::GetChatList(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            m_iUserId = data["id"].get<int>();
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }

    nlohmann::json GetChatList::ExecutePayload(ClientHandle &clientHandle)
    {
        auto pDataBase = DBAPI::DataBase::Get();
        const auto user = pDataBase->GetUserById(m_iUserId);
        const auto chatList = user.GetChatList();


        std::vector<nlohmann::json> jsnChatList;
        jsnChatList.reserve(chatList.size());


        for (const auto& chat : chatList)
            jsnChatList.push_back({{"id", chat.GetID()}});

        return {{"chats", jsnChatList}};
    }
}