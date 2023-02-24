#include "CreateChat.h"
#include "exceptions.h"
#include "../ClientHandle/ClientHandle.h"


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
        clientHandle.m_dbUser.CreateChat(m_sChatName);
        
        return {};
    }

} // Packet