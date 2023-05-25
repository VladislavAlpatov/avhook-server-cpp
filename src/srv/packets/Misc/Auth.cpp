//
// Created by nullifiedvlad on 08.12.2022.
//
#include "Auth.h"

#include <fmt/format.h>


#include "../../../lib/sqlite/connection.h"
#include "../../../lib/sha256/sha256.h"

#include "../../ClientHandle/ClientHandle.h"
#include "../../DataBaseAPI/DataBase.h"

#include "../exceptions.h"

namespace web::packet::misc
{

    Auth::Auth(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            m_sUserEmail = m_Data.at("email");

            const std::string password = m_Data.at("password");

            char hashedPass[65] = {0};
            sha256_easy_hash_hex(password.c_str(), password.size(), hashedPass);

            m_sUserPasswordHash = hashedPass;
        }
        catch (...)
        {
            throw Exception::CorruptedPacket();
        }
    }

    nlohmann::json Auth::ExecutePayload(ClientHandle &clientHandle)
    {

        auto pDataBase = dbapi::DataBase::Get();

        const auto user = pDataBase->GetUserByEmail(m_sUserEmail);

        if (user.GetPassword() != m_sUserPasswordHash)
            throw Exception::AuthFailedWrongPassword();


        clientHandle.m_dbUser = user;

		nlohmann::json out;
        out["user_id"] = user.GetID();

		return out;
    }
}// packet