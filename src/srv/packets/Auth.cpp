//
// Created by nullifiedvlad on 08.12.2022.
//
#include "Auth.h"
#include "../../lib/sqlite/connection.h"
#include "../../lib/sha256/sha256.h"
#include "fmt/format.h"
#include "exceptions.h"
#include "../ClientHandle/ClientHandle.h"


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

        auto pDataBase = sql::Connection::Get();

        auto res = pDataBase->Query(
				fmt::format(R"(SELECT `id` FROM `users` WHERE `password` = "{}" AND `email` = "{}")",
						m_sUserPasswordHash, m_sUserEmail));

        if (res.empty())
            throw Exception::AuthFailedWrongPassword();

        int iUserId = std::stoi(res[0][0]);

        clientHandle.m_iUserIdInDataBase = iUserId;

		nlohmann::json out;
		out["user_id"] = iUserId;

		return out;
    }
}// packet