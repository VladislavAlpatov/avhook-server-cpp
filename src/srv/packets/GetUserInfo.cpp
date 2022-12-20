//
// Created by nullifiedvlad on 13.12.2022.
//
#include "GetUserInfo.h"
#include "../../lib/sqlite/connection.h"
#include "exceptions.h"
#include <fmt/format.h>


namespace server::packet
{
    GetUserInfo::GetUserInfo(const nlohmann::json &data) : Base(data)
    {

    }

    std::string GetUserInfo::execute_payload(int userId)
    {

        const auto query = fmt::format("SELECT `id`, `name`, `status`, `type`, `email`,`is_online`, `in_game` FROM `users` WHERE `id` = {}", userId);

        const auto data = sql::Connection::get()->query(query);


        if (data.empty())
            throw exception::UserInfoNotFound();

        nlohmann::json outJson;
        outJson["id"]          = userId;
        outJson["name"]        = data[0][1];
        outJson["status"]      = data[0][2];
        outJson["type"]        = std::stoi(data[0][3]);
        outJson["is_online"]   = std::stoi(data[0][5]);
        outJson["in_game"]     = std::stoi(data[0][6]);
        outJson["email"] = data[0][4];

        return outJson.dump();
    }
} // packet