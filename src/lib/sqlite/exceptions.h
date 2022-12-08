//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <exception>

namespace sql::exception
{
    class FailedConnectToDataBase : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const override
        {
            return "Failed to open data base";
        }

    };
    class SyntaxError : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const override
        {
            return "SQL query contains syntax errors";
        }

    };
}