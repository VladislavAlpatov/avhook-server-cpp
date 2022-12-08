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

        char hashedPass[65] = {0};

        sha256_easy_hash_hex(password.c_str(), password.size(), hashedPass);

        auto res = sql::Connection::get()->query(fmt::format(R"(SELECT `id` FROM `users` WHERE `password` = "{}" AND `email` = "{}")", hashedPass, email) );

        if (res.empty())
            throw exception::AuthFailedWrongPassword();

        return res[0][0];
    }
}// packet