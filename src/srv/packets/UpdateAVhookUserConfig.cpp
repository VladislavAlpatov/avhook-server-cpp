//
// Created by nullifiedvlad on 19.12.2022.
//
#include "UpdateAVhookUserConfig.h"
#include "exceptions.h"
#include "../../lib/sqlite/connection.h"
#include "fmt/format.h"

namespace Web::packet
{
    UpdateAVhookUserConfig::UpdateAVhookUserConfig(const nlohmann::json &data) : Base(data)
    {
        try
        {
            m_iConfigId  = data["id"].get<int>();
            m_jsonConfig = data["data"].get<nlohmann::json>();
        }
        catch (...)
        {
            throw exception::CorruptedPacket();
        }
    }

    std::string UpdateAVhookUserConfig::execute_payload(int userId)
    {
        auto db = sql::Connection::get();

        if (db->query(fmt::format("SELECT `id` FROM `avhook-configs` WHERE `owner_id` = {} AND `id` = {}", userId, m_iConfigId)).empty())
            throw exception::ConfigNotFound();

        db->query(fmt::format("UPDATE `avhook-configs` SET `data` = '{}' WHERE `id` = {}", m_jsonConfig.dump(), m_iConfigId));

        return {};
    }
}