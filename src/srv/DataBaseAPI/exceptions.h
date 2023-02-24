//
// Created by alpat on 04.02.2023.
//

#pragma once
#include <exception>



namespace DBAPI::Exception
{
    class UserNotFound final : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "User not found";
        }
    };
    class UserNotInChat final : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "User not in chat";
        }
    };
    class UserAlreadyInChat final : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "User already in chat, impossible to add twice";
        }
    };
}

