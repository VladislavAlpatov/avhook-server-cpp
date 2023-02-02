#include "../ClientHandle/ClientHandle.h"
#include "DeleteChat.h"
#include "../../lib/sqlite/connection.h"
#include <fmt/format.h>

#include "exceptions.h"
namespace Web::Packet
{

    nlohmann::json Packet::DeleteChat::ExecutePayload(ClientHandle &clientHandle)
    {
        auto pDataBase = sql::Connection::Get();

        const auto res = pDataBase->Query(fmt::format("SELECT `owner_id` FROM `chats` WHERE `owner_id` = {} AND `id` = {}", clientHandle.m_iUserId, m_iChatId));

        if (res.empty())
            throw Exception::ChatDoesNotExist();

        pDataBase->Query(fmt::format("DELETE FROM `chats` WHERE `id` = {}", m_iChatId));

        return {};
    }

    DeleteChat::DeleteChat(const nlohmann::json &data) : BasePacket(data)
    {
        m_iChatId = data["chat_id"].get<int>();
    }
}