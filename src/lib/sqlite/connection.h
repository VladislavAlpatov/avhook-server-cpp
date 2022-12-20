//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <sqlite3.h>
#include <string>
#include <vector>
#include <mutex>

namespace sql
{

    class Connection
    {
    public:
        static Connection* get();
        Connection() = default;
        std::vector<std::vector<std::string>> query(const std::string& str);
        ~Connection();
    private:
        explicit Connection(const std::string& path);
        std::mutex m_lock;
        sqlite3* m_pDataBase = nullptr;

    };

} // sqlite3