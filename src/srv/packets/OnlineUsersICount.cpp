//
// Created by nullifiedvlad on 13.12.2022.
//
#include "OnlineUsersICount.h"
#include "../../lib/sqlite/connection.h"

namespace Web::packet
    {
        OnlineUsersICount::OnlineUsersICount(const nlohmann::json &data) : Base(data)
        {}

        std::string OnlineUsersICount::execute_payload(int userId)
        {
            auto dataBase = sql::Connection::get();
            const auto dt = dataBase->query("SELECT `id` FROM `users` WHERE `is_online` = TRUE");

            return std::to_string(dt.size());
        }
    } // packet