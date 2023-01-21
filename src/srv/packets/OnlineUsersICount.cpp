//
// Created by nullifiedvlad on 13.12.2022.
//
#include "OnlineUsersICount.h"
#include "../../lib/sqlite/connection.h"
#include "../server.h"
#include "../ClientHandle/ClientHandle.h"
namespace Web::Packet
    {
        OnlineUsersICount::OnlineUsersICount(const nlohmann::json &data) : BasePacket(data)
        {}

        nlohmann::json OnlineUsersICount::ExecutePayload(ClientHandle &clientHandle)
        {
			nlohmann::json out;
			out["users_online"] = Server::Get()->GetConnectionsCount();
            return out;
        }
    } // packet