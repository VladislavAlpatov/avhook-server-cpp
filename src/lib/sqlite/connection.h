//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <string>
#include <vector>
#include <mutex>
struct  sqlite3;
namespace sql
{

    class Connection
    {
    public:
        static Connection* Get();
        Connection() = default;
        std::vector<std::vector<std::string>> Query(const std::string& str);
        ~Connection();
    private:
        explicit Connection(const std::string& path);
        std::mutex m_lock;

        sqlite3* m_pDataBase = nullptr;

    };

} // sqlite3