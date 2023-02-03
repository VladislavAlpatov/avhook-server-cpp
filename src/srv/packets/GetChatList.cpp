#include "GetChatList.h"

#include "../../lib/sqlite/connection.h"
#include "../../lib/base64/base64.h"
#include "../ClientHandle/ClientHandle.h"

#include <fmt/format.h>


namespace Web::Packet
{

    GetChatList::GetChatList(const nlohmann::json &data) : BasePacket(data)
    {

    }

    nlohmann::json GetChatList::ExecutePayload(ClientHandle &clientHandle)
    {
        auto pDataBase = sql::Connection::Get();
        std::vector<nlohmann::json> chatList;
        const auto chatIds = pDataBase->Query(fmt::format("SELECT `chat_id` FROM `chats-members` WHERE `user_id` = {}",
                                                                                 clientHandle.m_iUserId));


        for (const auto& chatId : chatIds[0])
        {
            const auto chatInfo = pDataBase->Query(fmt::format("SELECT `id`,`name`,`owner_id`,`public_id` FROM `chat` WHERE `id` = {}", chatId));

            for (const auto& chatData : chatInfo)
            {
                nlohmann::json jsnChatInfo;

                int iChatId   = std::stoi(chatData[0]);
                int iOwnerId  = std::stoi(chatData[2]);
                int iPublicId = std::stoi(chatData[3]);

                jsnChatInfo["id"]          = iChatId;
                jsnChatInfo["name"]        = chatData[1];
                jsnChatInfo["owner_id"]    = iOwnerId;
                jsnChatInfo["invite_link"] = (clientHandle.m_iUserId == iOwnerId) ? base64::convert(iPublicId) : "";


                chatList.push_back(jsnChatInfo);
            }
        }
        return {{"chats", chatList}};
    }
}