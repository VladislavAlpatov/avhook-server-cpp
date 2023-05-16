//
// Created by vladislav on 09.03.23.
//
#include "UserRelated.h"
#include "../../DataBaseAPI/DataBase.h"

#include "../exceptions.h"

namespace web::packet::user
{

    UserRelated::UserRelated(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            auto pDataBase = dbapi::DataBase::Get();

            m_pUserFromPacket = pDataBase->GetUserById(data.at("id"));
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }
}