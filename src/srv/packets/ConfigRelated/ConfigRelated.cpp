//
// Created by Vladislav on 28.03.2023.
//

#include "ConfigRelated.h"
#include "../../DataBaseAPI/DataBase.h"


namespace Web::Packet::Config
{
    DBAPI::User ConfigRelated::GetUser()
    {
        return {};
    }

    ConfigRelated::ConfigRelated(const nlohmann::json &data) : BasePacket(data)
    {
        m_configFromPacket = DBAPI::DataBase::Get()->GetConfigById(data.at("id"));
    }

}