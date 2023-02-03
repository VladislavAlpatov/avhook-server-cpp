//
// Created by alpat on 04.02.2023.
//

#pragma once
#include <exception>



namespace DBAPI::Exception
{
class UserNotFound : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "User not found";
    }
};
}

