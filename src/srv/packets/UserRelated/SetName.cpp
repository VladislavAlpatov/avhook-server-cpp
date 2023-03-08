//
// Created by vladislav on 08.03.23.
//

#include "SetName.h"
#include "../exceptions.h"

#include "../../DataBaseAPI/DataBase.h"
#include "../../DataBaseAPI/User.h"
#include "../../ClientHandle/ClientHandle.h"

namespace Web::Packet::User
{
    SetName::SetName(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            m_iUserID      = data["id"].get<int>();
            m_sNewUserName = data["name"].get<std::string>();
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }
    nlohmann::json SetName::ExecutePayload(Web::ClientHandle &clientHandle)
    {
        auto pDataBase = DBAPI::DataBase::Get();

        auto targetUser = pDataBase->GetUserById(m_iUserID);

        if (targetUser != clientHandle.m_dbUser)
            throw std::runtime_error("You cant change other user data without admin rights");

        targetUser.SetName(m_sNewUserName);

        return {};
    }
}