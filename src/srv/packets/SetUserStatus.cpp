//
// Created by nullifiedvlad on 19.12.2022.
//
#include "SetUserStatus.h"
#include "../ClientHandle/ClientHandle.h"
#include "exceptions.h"
#include "../DataBaseAPI/DataBase.h"
#include "../DataBaseAPI/User.h"


namespace Web::Packet
{
    SetUserStatus::SetUserStatus(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            m_sNewUserStatus = m_Data["status"].get<std::string>();
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }

    nlohmann::json SetUserStatus::ExecutePayload(ClientHandle &clientHandle)
    {
        auto user = DBAPI::DataBase::Get()->GetUserById(clientHandle.m_iUserId);
        user.SetStatus(m_sNewUserStatus);

        return {};
    }

} // packet