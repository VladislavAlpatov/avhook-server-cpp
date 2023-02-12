#include "CreateChat.h"
#include "exceptions.h"
#include "../../lib/sqlite/connection.h"
#include <boost/algorithm/string/replace.hpp>
#include <fmt/format.h>
#include "../../lib/base64/base64.h"
#include "../ClientHandle/ClientHandle.h"
#include "../DataBaseAPI/DataBase.h"
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
        return {};
    }

    size_t CreateChat::CreateChatPublicId()
    {
        std::srand(time(NULL));
        auto pDataBase = DBAPI::DataBase::Get();

        while (true)
        {
            const auto id = std::rand();

            if (!pDataBase->IsChatExist(id))
                return id;

        }
    }
} // Packet