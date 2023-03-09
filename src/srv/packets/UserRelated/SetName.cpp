//
// Created by vladislav on 08.03.23.
//

#include "SetName.h"
#include "../exceptions.h"

#include "../../DataBaseAPI/DataBase.h"
#include "../../ClientHandle/ClientHandle.h"

namespace Web::Packet::User
{
    SetName::SetName(const nlohmann::json &data) : UserRelated(data)
    {
        try
        {
            m_sNewUserName = data.at("name");
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }
    nlohmann::json SetName::ExecutePayload(Web::ClientHandle &clientHandle)
    {
        if (m_userFromPacket != clientHandle.m_dbUser)
            throw std::runtime_error("You cant change other user data without admin rights");

        m_userFromPacket.SetName(m_sNewUserName);

        return {};
    }
}