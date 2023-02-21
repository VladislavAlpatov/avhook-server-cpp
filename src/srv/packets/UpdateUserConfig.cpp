//
// Created by nullifiedvlad on 19.12.2022.
//
#include "UpdateUserConfig.h"
#include "exceptions.h"
#include "../ClientHandle/ClientHandle.h"

#include "../DataBaseAPI/Config.h"

#include <algorithm>



namespace Web::Packet
{
    UpdateUserConfig::UpdateUserConfig(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            m_iConfigId  = data["id"].get<int>();
            m_jsonConfig = data["data"].get<nlohmann::json>();
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }

    nlohmann::json UpdateUserConfig::ExecutePayload(ClientHandle &clientHandle)
    {
        auto userCfgs = clientHandle.m_dbUser.GetConfigs();
        auto cfg = std::find_if(userCfgs.begin(), userCfgs.end(),
                                [this](const DBAPI::Config& cfg)
                                {
                                    return cfg.GetID() == m_iConfigId;
                                } );
        if (cfg == userCfgs.end())
            throw Exception::ConfigNotFound();

        cfg->SetData(m_jsonConfig);

        return {};
    }
}