//
// Created by nullifiedvlad on 20.12.2022.
//
#include "GetUserConfigs.h"
#include "exceptions.h"
#include "../../lib/sqlite/connection.h"
#include "fmt/format.h"


namespace Web::Packet
{
    nlohmann::json GetUserConfigs::ExecutePayload(int userId)
    {
        std::vector<nlohmann::json> cfgs;
        nlohmann::json out;
        for (const auto& cfgData : sql::Connection::Get()->Query(
				fmt::format("SELECT `id`, `data` FROM `avhook-configs` WHERE `owner_id` = {}", userId)))
        {
            nlohmann::json tmp;
            tmp["id"]   = std::stoi(cfgData[0]);
            tmp["data"] = nlohmann::json::parse(cfgData[1]);
            cfgs.push_back(tmp);
        }

        out["configs"] = cfgs;

        return out;
    }

    GetUserConfigs::GetUserConfigs(const nlohmann::json &data) : BasePacket(data)
    {}
} // packet