//
// Created by nullifiedvlad on 06.12.2022.
//
#include "SetUserName.h"
#include <fmt/format.h>
#include "../../lib/sqlite/connection.h"
#include "exceptions.h"
namespace server::packet
{

    SetUserName::SetUserName(const nlohmann::json &data) : Base(data)
    {

    }

    std::string SetUserName::execute_payload(int userId)
    {
        const auto data = sql::Connection::get()->query(fmt::format("UPDATE `users` SET `name`= \"{}\" WHERE `id` = {}", m_Data["name"].get<std::string>(), userId));

        if (data.empty())
            throw exception::UserInfoNotFound();
    }
} // packet