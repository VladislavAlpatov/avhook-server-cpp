//
// Created by Vladislav on 28.03.2023.
//

#include "GetConfigs.h"
#include "../../DataBaseAPI/Config.h"


namespace web::packet::user
{
    nlohmann::json GetConfigs::ExecutePayload(web::ClientHandle &clientHandle)
    {
        std::vector<nlohmann::json> jsnCfgList;
        auto cfgs = m_pUserFromPacket.GetConfigs();
        jsnCfgList.reserve(cfgs.size());

        for (const auto& cfg : cfgs)
            jsnCfgList.push_back({{"id", cfg.GetID()}});

        return {{"configs", jsnCfgList}};
    }

    GetConfigs::GetConfigs(const nlohmann::json &data) : UserRelated(data)
    {

    }

}