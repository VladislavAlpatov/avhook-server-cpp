//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <string>
#include <vector>
struct  sqlite3;
namespace sql
{

    class Connection
    {
    public:
        explicit Connection(const std::string& path);
        Connection() = default;
        std::vector<std::vector<std::string>> Query(const std::string& str);
        ~Connection();
    private:
        sqlite3* m_pDataBase = nullptr;

    };

} // sqlite3