//
// Created by vladislav on 09.03.23.
//
#include "UserRelated.h"
#include "../../DataBaseAPI/DataBase.h"

#include "../exceptions.h"

namespace Web::Packet::User
{

    UserRelated::UserRelated(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            auto pDataBase = DBAPI::DataBase::Get();

            m_userFromPacket = pDataBase->GetUserById(data.at("id"));
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }
}