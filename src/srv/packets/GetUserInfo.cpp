//
// Created by nullifiedvlad on 13.12.2022.
//
#include "GetUserInfo.h"
#include "../../lib/sqlite/connection.h"
#include "exceptions.h"
#include <fmt/format.h>
#include "../ClientHandle/ClientHandle.h"

namespace Web::Packet
{
    GetUserInfo::GetUserInfo(const nlohmann::json &data) : BasePacket(data)
    {

    }

    nlohmann::json GetUserInfo::ExecutePayload(ClientHandle &clientHandle)
    {

        const auto query = fmt::format("SELECT `id`, `name`, `status`, `type`, `email` FROM `users` WHERE `id` = {}",
                                       clientHandle.m_iUserIdInDataBase );

        const auto data = sql::Connection::Get()->Query(query);


        if (data.empty())
            throw Exception::UserInfoNotFound();

        nlohmann::json outJson;
        outJson["id"]          = clientHandle.m_iUserIdInDataBase;
        outJson["name"]        = data[0][1];
        outJson["status"]      = data[0][2];
        outJson["type"]        = std::stoi(data[0][3]);
        outJson["email"] = data[0][4];

        return outJson;
    }
} // packet