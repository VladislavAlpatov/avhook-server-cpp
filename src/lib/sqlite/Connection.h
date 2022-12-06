//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <sqlite3.h>
#include <string>
#include <vector>


namespace sql
{

    class Connection
    {
    public:
        Connection(const std::string& path);

        std::vector<std::vector<std::string>> query(const std::string& str);
    private:
        sqlite3* m_pDataBase;

    };

} // sqlite3