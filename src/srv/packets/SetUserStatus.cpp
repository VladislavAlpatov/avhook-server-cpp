//
// Created by nullifiedvlad on 19.12.2022.
//
#include "SetUserStatus.h"
#include "../../lib/sqlite/connection.h"

#include "exceptions.h"
#include <fmt/format.h>


namespace Web::packet
{
    SetUserStatus::SetUserStatus(const nlohmann::json &data) : Base(data)
    {
        try
        {
            m_sNewUserStatus = m_Data["status"].get<std::string>();
        }
        catch (...)
        {
            throw exception::CorruptedPacket();
        }
    }

    std::string SetUserStatus::execute_payload(int userId)
    {
        sql::Connection::get()->query(fmt::format("UPDATE `users` SET `status`= \"{}\" WHERE `id` = {}", m_sNewUserStatus, userId));
        return "";
    }

} // packet