#include "GetChatList.h"

#include "../../lib/sqlite/connection.h"
#include "../../lib/base64/base64.h"
#include "../ClientHandle/ClientHandle.h"
#include "../DataBaseAPI/DataBase.h"

#include <fmt/format.h>


namespace Web::Packet
{

    GetChatList::GetChatList(const nlohmann::json &data) : BasePacket(data)
    {

    }

    nlohmann::json GetChatList::ExecutePayload(ClientHandle &clientHandle)
    {
        return {};
    }
}