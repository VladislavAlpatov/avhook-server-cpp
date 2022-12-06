//
// Created by nullifiedvlad on 06.12.2022.
//
#include "SetUserName.h"
#include <fmt/format.h>
namespace server::packet
{

    SetUserName::SetUserName(const nlohmann::json &data, sql::Connection* pConn) : Base(data)
    {
        m_pConn = pConn;

    }

    std::string SetUserName::execute_payload()
    {
        m_pConn->query(fmt::format("UPDATE `users` SET `name`= \"{}\" WHERE `id` = 1", m_Data["name"].get<std::string>()));

        return "";
    }
} // packet