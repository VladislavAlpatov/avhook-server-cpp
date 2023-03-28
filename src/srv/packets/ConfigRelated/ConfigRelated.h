//
// Created by Vladislav on 28.03.2023.
//

#pragma once
#include "../BasePacket.h"
#include "../interfaces/IUserAccessible.h"
#include "../../DataBaseAPI/Config.h"


namespace Web::Packet::Config
{
    class ConfigRelated : public BasePacket, public IUserAccessible
    {
    public:
        ConfigRelated(const nlohmann::json &data);
        DBAPI::User GetUser() override;
    protected:
        DBAPI::Config m_configFromPacket;
    };

}