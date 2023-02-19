//
// Created by nullifiedvlad on 13.12.2022.
//
#include "GetUserInfo.h"
#include "exceptions.h"
#include "../ClientHandle/ClientHandle.h"
#include "../DataBaseAPI/DataBase.h"
#include "../DataBaseAPI/User.h"

namespace Web::Packet
{
    GetUserInfo::GetUserInfo(const nlohmann::json &data) : BasePacket(data)
    {

    }

    nlohmann::json GetUserInfo::ExecutePayload(ClientHandle &clientHandle)
    {
        nlohmann::json outJson;


        outJson["id"]          = clientHandle.m_dbUser.GetID();
        outJson["name"]        = clientHandle.m_dbUser.GetName();
        outJson["status"]      = clientHandle.m_dbUser.GetStatus();
        outJson["type"]        = clientHandle.m_dbUser.GetType();
        outJson["email"]       = clientHandle.m_dbUser.GetEmail();


        return {};
    }
} // packet