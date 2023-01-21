//
// Created by nullifiedvlad on 19.12.2022.
//
#include "SetUserStatus.h"
#include "../../lib/sqlite/connection.h"
#include "../ClientHandle/ClientHandle.h"
#include "exceptions.h"
#include <fmt/format.h>


namespace Web::Packet
{
    SetUserStatus::SetUserStatus(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            m_sNewUserStatus = m_Data["status"].get<std::string>();
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }

    nlohmann::json SetUserStatus::ExecutePayload(ClientHandle &clientHandle)
    {
		sql::Connection::Get()->Query(
				fmt::format("UPDATE `users` SET `status`= \"{}\" WHERE `id` = {}",
                            m_sNewUserStatus, clientHandle.m_iUserIdInDataBase));
        return {};
    }

} // packet