//
// Created by vladislav on 07.03.23.
//

#include "GetName.h"


#include "../../DataBaseAPI/DataBase.h"

namespace Web::Packet::User
{
    nlohmann::json GetName::ExecutePayload(ClientHandle &clientHandle)
    {

        auto pDataBase = DBAPI::DataBase::Get();

        const auto user = pDataBase->GetUserById(m_iUserId);

        return {{"name", user.GetName()}};
    }

    GetName::GetName(const nlohmann::json &data) : UserRelated(data)
    {

    }
} // User