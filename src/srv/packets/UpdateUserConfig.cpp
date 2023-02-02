//
// Created by nullifiedvlad on 19.12.2022.
//
#include "UpdateUserConfig.h"
#include "exceptions.h"
#include "../../lib/sqlite/connection.h"
#include "../ClientHandle/ClientHandle.h"
#include "fmt/format.h"

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
        auto db = sql::Connection::Get();

        if (db->Query(fmt::format("SELECT `id` FROM `configs` WHERE `owner_id` = {} AND `id` = {}", clientHandle.m_iUserId,
                                  m_iConfigId)).empty())
            throw Exception::ConfigNotFound();

		db->Query(fmt::format("UPDATE `configs` SET `data` = '{}' WHERE `id` = {}", m_jsonConfig.dump(),
				m_iConfigId));

        return {};
    }
}