#include "../ClientHandle/ClientHandle.h"
#include "DeleteChat.h"
#include <fmt/format.h>

#include "exceptions.h"
#include "../DataBaseAPI/DataBase.h"

namespace Web::Packet
{

    nlohmann::json Packet::DeleteChat::ExecutePayload(ClientHandle &clientHandle)
    {

        return {};
    }

    DeleteChat::DeleteChat(const nlohmann::json &data) : BasePacket(data)
    {
        m_iChatId = data["chat_id"].get<int>();
    }
}