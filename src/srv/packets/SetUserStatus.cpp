//
// Created by nullifiedvlad on 19.12.2022.
//
#include "SetUserStatus.h"
#include "../../lib/sqlite/connection.h"

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

    nlohmann::json SetUserStatus::ExecutePayload(int userId)
    {
		sql::Connection::Get()->Query(
				fmt::format("UPDATE `users` SET `status`= \"{}\" WHERE `id` = {}", m_sNewUserStatus, userId));
        return {};
    }

} // packet