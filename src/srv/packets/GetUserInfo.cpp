//
// Created by nullifiedvlad on 13.12.2022.
//
#include "GetUserInfo.h"
#include "../../lib/sqlite/connection.h"
namespace server::packet
    {
    GetUserInfo::GetUserInfo(const nlohmann::json &data) : Base(data)
    {}

    std::string GetUserInfo::execute_payload(int userId)
    {
        sql::Connection::get()->query("SELECT `id`, `name`, `status`, `type` WHERE `id` = {}");
    }
} // packet