//
// Created by nullifiedvlad on 19.12.2022.
//
#include "UpdateUserConfig.h"
#include "exceptions.h"
#include "../../lib/sqlite/connection.h"
#include "../ClientHandle/ClientHandle.h"
#include "fmt/format.h"
#include "../DataBaseAPI/DataBase.h"

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

        return {};
    }
}