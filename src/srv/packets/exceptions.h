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
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Client auth was failed, wrong password";
        }
    };

    class CorruptedPacket final  : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Accepted package was corrupted";
        }
    };
    class AnotherSessionWithClientAlreadyExist final  : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Only one connection can be linked with user in data base";
        }
    };

    class UserInfoNotFound final  : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Information about this user does not exist";
        }
    };
    class ConfigNotFound final : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Failed to find avhook config";
        }
    };

}