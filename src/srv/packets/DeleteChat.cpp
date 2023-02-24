#include "../ClientHandle/ClientHandle.h"
#include "DeleteChat.h"
#include "../DataBaseAPI/DataBase.h"
#include "exceptions.h"


namespace Web::Packet
{

    DeleteChat::DeleteChat(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            m_iChatId = data["chat_id"].get<int>();
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }

    nlohmann::json Packet::DeleteChat::ExecutePayload(ClientHandle &clientHandle)
    {

        return {};
    }
}