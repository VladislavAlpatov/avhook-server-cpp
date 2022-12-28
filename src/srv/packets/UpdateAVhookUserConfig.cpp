//
// Created by nullifiedvlad on 19.12.2022.
//
#include "UpdateAVhookUserConfig.h"
#include "exceptions.h"
#include "../../lib/sqlite/connection.h"
#include "fmt/format.h"

namespace Web::Packet
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
            throw Exception::CorruptedPacket();
        }
    }

    nlohmann::json UpdateAVhookUserConfig::ExecutePayload(int userId)
    {
        auto db = sql::Connection::Get();

        if (db->Query(fmt::format("SELECT `id` FROM `avhook-configs` WHERE `owner_id` = {} AND `id` = {}", userId,
				m_iConfigId)).empty())
            throw Exception::ConfigNotFound();

		db->Query(fmt::format("UPDATE `avhook-configs` SET `data` = '{}' WHERE `id` = {}", m_jsonConfig.dump(),
				m_iConfigId));

        return {};
    }
}