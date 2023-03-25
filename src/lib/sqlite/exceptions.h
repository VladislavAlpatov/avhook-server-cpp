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
        const char *what() const noexcept override
        {
            return "Failed to open data base";
        }

    };
class DataBaseFileNotFound : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return ".db file was not found";
    }
};
    class SyntaxError : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "SQL Query contains syntax errors";
        }

    };
}