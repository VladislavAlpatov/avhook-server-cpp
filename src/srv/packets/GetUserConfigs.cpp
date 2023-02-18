//
// Created by nullifiedvlad on 20.12.2022.
//
#include "GetUserConfigs.h"
#include "../../lib/sqlite/connection.h"
#include "../ClientHandle/ClientHandle.h"
#include "../DataBaseAPI/DataBase.h"


#include <fmt/format.h>

namespace Web::Packet
{
    nlohmann::json GetUserConfigs::ExecutePayload(ClientHandle &clientHandle)
    {

        return {};
    }

    GetUserConfigs::GetUserConfigs(const nlohmann::json &data) : BasePacket(data)
    {
        
    }
} // packet