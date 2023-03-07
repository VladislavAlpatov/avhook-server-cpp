//
// Created by nullifiedvlad on 08.12.2022.
//
#include "Auth.h"

#include <fmt/format.h>


#include "../../../lib/sqlite/connection.h"
#include "../../../lib/sha256/sha256.h"

#include "../../ClientHandle/ClientHandle.h"
#include "../../DataBaseAPI/DataBase.h"
#include "../../DataBaseAPI/User.h"

#include "../exceptions.h"

namespace Web::Packet
{

    Auth::Auth(const nlohmann::json &data) : BasePacket(data)
    {
        try
        {
            m_sUserEmail = m_Data["email"].get<std::string>();

            const auto password = m_Data["password"].get<std::string>();

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

        auto pDataBase = DBAPI::DataBase::Get();

        const auto user = pDataBase->GetUserByEmail(m_sUserEmail);

        if (user.GetPassword() != m_sUserPasswordHash)
            throw Exception::AuthFailedWrongPassword();


        clientHandle.m_dbUser = user;

		nlohmann::json out;
        out["user_id"] = user.GetID();

		return out;
    }
}// packet