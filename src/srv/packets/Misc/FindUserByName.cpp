//
// Created by vlad on 25.05.23.
//

#include "FindUserByName.h"
#include "../exceptions.h"
#include "../../DataBaseAPI/DataBase.h"
#include "../../DataBaseAPI/User.h"


web::packet::misc::FindUserByName::FindUserByName(const nlohmann::json &data) : BasePacket(data)
{
    try
    {
        m_sSearchName = data.at("name");
    }
    catch(...)
    {
        throw Exception::CorruptedPacket();
    }
}

nlohmann::json web::packet::misc::FindUserByName::ExecutePayload(web::ClientHandle &clientHandle)
{
    const auto database = dbapi::DataBase::Get();

    std::vector<uint64_t> usersIds;

    for (const auto& user : database->GetUsersByName(m_sSearchName))
        usersIds.push_back(user.GetID());


    return {{"users_ids", usersIds}};
}
