//
// Created by nullifiedvlad on 13.12.2022.
//
#include "GetUserInfo.h"
#include "../ClientHandle/ClientHandle.h"
#include "../DataBaseAPI/DataBase.h"

namespace Web::Packet
{

    nlohmann::json GetUserInfo::ExecutePayload(ClientHandle &clientHandle)
    {
        nlohmann::json outJson = clientHandle.m_dbUser.ToJson();
        outJson["email"]       = clientHandle.m_dbUser.GetEmail();

        return outJson;
    }
} // packet