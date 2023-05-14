//
// Created by Vladislav on 28.03.2023.
//

#pragma once
#include "../BasePacket.h"
#include "../interfaces/IUserAccessible.h"
#include "../../DataBaseAPI/Config.h"


namespace web::packet::config
{
    class ConfigRelated : public BasePacket, public IUserAccessible
    {
    public:
        ConfigRelated(const nlohmann::json &data);
        dbapi::User GetUser() override;
    protected:
        dbapi::Config m_configFromPacket;
    };

}