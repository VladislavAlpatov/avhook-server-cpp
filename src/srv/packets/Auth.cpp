//
// Created by nullifiedvlad on 08.12.2022.
//
#include "Auth.h"
#include "../../lib/sqlite/connection.h"
#include "../../lib/sha256/sha256.h"
#include "fmt/format.h"
#include "exceptions.h"
namespace server::packet
{

    Auth::Auth(const nlohmann::json &data) : Base(data)
    {

    }

    std::string Auth::execute_payload(int userId)
    {
        const auto password = m_Data["password"].get<std::string>();
        const auto email    = m_Data["email"].get<std::string>();
        auto pDataBase =sql::Connection::get();

        char hashedPass[65] = {0};


        sha256_easy_hash_hex(password.c_str(), password.size(), hashedPass);

        auto res = pDataBase->query(fmt::format(R"(SELECT `id` FROM `users` WHERE `password` = "{}" AND `email` = "{}")", hashedPass, email) );

        if (res.empty())
            throw exception::AuthFailedWrongPassword();
        int iUserId = std::stoi(res[0][0]);


        bool bIsAlreadyOnline = std::stoi(pDataBase->query(fmt::format("SELECT `is_online` FROM `users` WHERE `id` = {}", iUserId))[0][0] );

        if (bIsAlreadyOnline)
            throw exception::AnotherSessionWithClientAlreadyExist();

        return res[0][0];
    }
}// packet