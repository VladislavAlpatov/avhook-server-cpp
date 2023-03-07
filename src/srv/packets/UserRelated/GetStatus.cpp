//
// Created by vladislav on 07.03.23.
//

#include "GetStatus.h"

#include "../../DataBaseAPI/DataBase.h"
#include "../../DataBaseAPI/User.h"

namespace Web::Packet::User
{

    nlohmann::json GetStatus::ExecutePayload(ClientHandle &clientHandle)
    {
        auto pDataBase = DBAPI::DataBase::Get();

        const auto user = pDataBase->GetUserById(m_iUserId);

        return {{"Status", user.GetStatus()}};
    }

    GetStatus::GetStatus(const nlohmann::json &data) : BasePacket(data)
    {

    }
}