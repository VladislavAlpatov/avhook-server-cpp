//
// Created by nullifiedvlad on 08.12.2022.
//
#pragma once
#include <stdexcept>

namespace server::packet::exception
{
    class AuthFailedWrongPassword final : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const override
        {
            return "Client auth was failed, wrong password";
        }
    };

    class CorruptedPacket final  : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const override
        {
            return "Accepted package was corrupted";
        }
    };
    class AnotherSessionWithClientAlreadyExist final  : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const override
        {
            return "Only one connection can be linked with user in data base";
        }
    };

}