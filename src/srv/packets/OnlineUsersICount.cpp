//
// Created by nullifiedvlad on 13.12.2022.
//
#include "OnlineUsersICount.h"
#include "../../lib/sqlite/connection.h"

namespace Web::Packet
    {
        OnlineUsersICount::OnlineUsersICount(const nlohmann::json &data) : BasePacket(data)
        {}

        nlohmann::json OnlineUsersICount::ExecutePayload(int userId)
        {
            auto dataBase = sql::Connection::Get();
            const auto dt = dataBase->Query("SELECT `id` FROM `users` WHERE `is_online` = TRUE");
			nlohmann::json out;
			out["users_online"] = dt.size();
            return out;
        }
    } // packet