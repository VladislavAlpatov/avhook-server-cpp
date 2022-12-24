//
// Created by nullifiedvlad on 08.12.2022.
//
#include "Auth.h"
#include "../../lib/sqlite/connection.h"
#include "../../lib/sha256/sha256.h"
#include "fmt/format.h"
#include "exceptions.h"
namespace Web::packet
{

    Auth::Auth(const nlohmann::json &data) : Base(data)
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
            throw exception::CorruptedPacket();
        }
    }

    std::string Auth::execute_payload(int userId)
    {

        auto pDataBase =sql::Connection::get();

        auto res = pDataBase->query(fmt::format(R"(SELECT `id` FROM `users` WHERE `password` = "{}" AND `email` = "{}")", m_sUserPasswordHash, m_sUserEmail) );

        if (res.empty())
            throw exception::AuthFailedWrongPassword();

        int iUserId = std::stoi(res[0][0]);


        bool bIsAlreadyOnline = std::stoi(pDataBase->query(fmt::format("SELECT `is_online` FROM `users` WHERE `id` = {}", iUserId))[0][0] );

        return res[0][0];
    }
}// packet