//
// Created by nullifiedvlad on 20.12.2022.
//
#include "GetUserConfigs.h"
#include "../ClientHandle/ClientHandle.h"
#include "../DataBaseAPI/Config.h"

namespace Web::Packet
{
    nlohmann::json GetUserConfigs::ExecutePayload(ClientHandle &clientHandle)
    {
        std::vector<nlohmann::json> jsnLst;

        for (const auto& cfg : clientHandle.m_dbUser.GetConfigs())
        {
            nlohmann::json cfgInfo;
            cfgInfo["data"] = cfg.GetData();
            cfgInfo["id"]  = cfg.GetID();

            jsnLst.push_back({
                {"data", cfg.GetData()},
                {"id", cfg.GetID()},
                             });
        }

        nlohmann::json out;

        out["configs"] = jsnLst;

        return out;
    }

    GetUserConfigs::GetUserConfigs(const nlohmann::json &data) : BasePacket(data)
    {
        
    }
} // packet