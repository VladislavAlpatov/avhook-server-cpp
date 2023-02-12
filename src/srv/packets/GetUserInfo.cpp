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

        auto user = DBAPI::DataBase::Get()->GetUserById(clientHandle.m_iUserId);


        nlohmann::json outJson;
        outJson["id"]          = clientHandle.m_iUserId;
        outJson["name"]        = user.GetName();
        outJson["status"]      = user.GetStatus();
        outJson["type"]        = user.GetType();
        outJson["email"]       = user.GetEmail();


        return {};
    }
} // packet