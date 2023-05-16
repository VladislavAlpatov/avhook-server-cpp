//
// Created by Vladislav on 28.03.2023.
//

#include "ConfigRelated.h"
#include "../../DataBaseAPI/DataBase.h"
#include "../exceptions.h"


namespace web::packet::config
{
    dbapi::User ConfigRelated::GetUser()
    {
        return m_configFromPacket.GetOwner();
    }

    ConfigRelated::ConfigRelated(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            m_configFromPacket = dbapi::DataBase::Get()->GetConfigById(data.at("id"));
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }

}