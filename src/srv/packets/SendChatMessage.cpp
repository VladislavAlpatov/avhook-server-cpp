//
// Created by Vlad on 1/5/2023.
//

#include "SendChatMessage.h"
#include "exceptions.h"
#include "../ClientHandle/ClientHandle.h"
#include "../DataBaseAPI/Chat.h"
#include <algorithm>


namespace Web::Packet
{

    SendChatMessage::SendChatMessage(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            m_sText   = data["text"].get<std::string>();
            m_iChatId = data["chat_id"].get<int>();
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }

    nlohmann::json SendChatMessage::ExecutePayload(ClientHandle &clientHandle)
    {

        auto chats  = clientHandle.m_dbUser.GetChatList();

        auto chat = std::find_if(chats.begin(), chats.end(),
                                [this](const DBAPI::Chat& chat)
                                {
                                    return chat.GetID() == m_iChatId;
                                } );

        if (chat == chats.end())
            throw Exception::ChatDoesNotExist();


        chat->SendMessage(clientHandle.m_dbUser, m_sText);
        return {};
    }
} // Packets
