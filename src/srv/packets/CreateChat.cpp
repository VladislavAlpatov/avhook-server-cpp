#include "CreateChat.h"
#include "exceptions.h"
#include "../../lib/sqlite/connection.h"
#include <boost/algorithm/string/replace.hpp>
#include <fmt/format.h>
#include "../../lib/base64/base64.h"
#include "../ClientHandle/ClientHandle.h"
#include <random>

namespace Web::Packet
{
    CreateChat::CreateChat(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            m_sChatName = data["chat_name"].get<std::string>();
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }

    nlohmann::json CreateChat::ExecutePayload(ClientHandle &clientHandle)
    {
        auto pCon = sql::Connection::Get();

        boost::replace_all(m_sChatName, "'", "''");
        boost::replace_all(m_sChatName, "\"", "\"\"");
        const auto iPublicId = CreateChatPublicId();

        pCon->Query(fmt::format("INSERT INTO `chats` (`owner_id`, `name`, `public_id`) VALUES({},'{}',{})",
                                clientHandle.m_iUserIdInDataBase, m_sChatName, iPublicId));

        auto iChatId = pCon->Query(fmt::format("SELECT `id` FROM `chats` WHERE `public_id` = {}", iPublicId))[0][0];
        pCon->Query(fmt::format("INSERT INTO `chats-members` (`chat_id`, `user_id`) VALUES({},{})", iChatId,clientHandle.m_iUserIdInDataBase));

        return {};
    }

    size_t CreateChat::CreateChatPublicId()
    {
        std::srand(time(NULL));
        auto pCon = sql::Connection::Get();

        while (true)
        {
            const auto id = std::rand();

            if (!pCon->Query(fmt::format("SELECT `id` FROM `chats` WHERE `id` = {}", id)).empty())
                continue;

            return id;
        }
    }
} // Packet