//
// Created by nullifiedvlad on 06.12.2022.
//
#include "connection.h"
#include "exceptions.h"
#include "../../consts.h"
#include <sqlite3.h>
#include <filesystem>

namespace sql
{
    Connection::Connection(const std::string &path)
    {
        if (!std::filesystem::exists(path))
            throw exception::DataBaseFileNotFound();

        if (sqlite3_open(path.c_str(), &m_pDataBase) != SQLITE_OK)
            throw exception::FailedConnectToDataBase();
    }

    std::vector<std::vector<std::string>> Connection::Query(const std::string &str)
    {
        std::vector<std::vector<std::string>> out;

        sqlite3_stmt* pSqliteStatement = nullptr;

        sqlite3_prepare_v2(m_pDataBase, str.c_str(), (int)str.size(), &pSqliteStatement, nullptr);

        if (!pSqliteStatement)
            throw exception::SyntaxError();

        while (sqlite3_step(pSqliteStatement) != SQLITE_DONE)
        {

            const auto rowLength = sqlite3_column_count(pSqliteStatement);
            std::vector<std::string> rowData;
            rowData.reserve(rowLength);

            for (int i =0; i < rowLength; ++i)
            {
                const auto pText = sqlite3_column_text(pSqliteStatement, i);
                if (sqlite3_column_type(pSqliteStatement, i) != SQLITE_BLOB || !pText)
                    rowData.emplace_back((pText) ? (const char*)pText : "");
            }
            out.emplace_back(rowData);
        }
        sqlite3_finalize(pSqliteStatement);
        return out;
    }

    Connection::~Connection()
    {
        if (m_pDataBase)
            sqlite3_close(m_pDataBase);
    }

} // sqlite3