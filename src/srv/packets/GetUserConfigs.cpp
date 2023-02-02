//
// Created by nullifiedvlad on 20.12.2022.
//
#include "GetUserConfigs.h"
#include "../../lib/sqlite/connection.h"
#include "../ClientHandle/ClientHandle.h"


#include <fmt/format.h>

namespace Web::Packet
{
    nlohmann::json GetUserConfigs::ExecutePayload(ClientHandle &clientHandle)
    {
        std::vector<nlohmann::json> cfgs;
        nlohmann::json out;
        const auto cfgList = sql::Connection::Get()->Query(
                fmt::format("SELECT `id`, `data` FROM `configs` WHERE `owner_id` = {}", clientHandle.m_iUserId));

        for (const auto& cfgData : cfgList)
        {
            nlohmann::json cfgJson;
            cfgJson["id"]   = std::stoi(cfgData[0]);
            cfgJson["data"] = nlohmann::json::parse(cfgData[1]);
            cfgs.push_back(cfgJson);
        }
        
        out["configs"] = cfgs;

        return out;
    }

    GetUserConfigs::GetUserConfigs(const nlohmann::json &data) : BasePacket(data)
    {}
} // packet