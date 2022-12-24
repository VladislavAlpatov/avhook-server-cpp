//
// Created by nullifiedvlad on 06.12.2022.
//
#include "SetUserName.h"
#include <fmt/format.h>
#include "../../lib/sqlite/connection.h"
#include "exceptions.h"
namespace Web::packet
{

    SetUserName::SetUserName(const nlohmann::json &data) : Base(data)
    {
        try
        {
            m_sNewUserName = m_Data["name"].get<std::string>();
        }
        catch (...)
        {
            throw exception::CorruptedPacket();
        }
    }

    std::string SetUserName::execute_payload(int userId)
    {
        if (!is_username_valid(m_sNewUserName))
            return "";

        sql::Connection::get()->query(fmt::format("UPDATE `users` SET `name`= \"{}\" WHERE `id` = {}", m_sNewUserName, userId));

        return "";
    }

    bool SetUserName::is_username_valid(const std::string &name)
    {
        for (const auto chr : name)
            if (chr == ' ' or chr == '\n' or chr == '\t')
                return false;
        return true;
    }
} // packet