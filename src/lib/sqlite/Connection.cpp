//
// Created by nullifiedvlad on 06.12.2022.
//
#include "Connection.h"
#include "exceptions.h"
namespace sql
{
    Connection::Connection(const std::string &path)
    {
        if (sqlite3_open(R"(C:\Users\Vlad\Desktop\db.db)", &m_pDataBase) != SQLITE_OK)
            throw exception::FailedConnectToDataBase();
    }

    std::vector<std::vector<std::string>> Connection::query(const std::string &str)
    {
        std::vector<std::vector<std::string>> out;

        sqlite3_stmt* pSqliteStatement;
        sqlite3_prepare_v2(m_pDataBase, str.c_str(), -1, &pSqliteStatement, nullptr);

        while (sqlite3_step(pSqliteStatement) != SQLITE_DONE)
        {
            const auto rowLength = sqlite3_column_count(pSqliteStatement);
            std::vector<std::string> rowData;
            rowData.reserve(rowLength);

            for (size_t i =0; i < rowLength; ++i)
            {
                const auto pText = sqlite3_column_text(pSqliteStatement, i);

                if (sqlite3_column_type(pSqliteStatement, i) != SQLITE_BLOB or !pText)
                    rowData.emplace_back((pText) ? (const char*)pText : "");
            }

            out.emplace_back(rowData);
        }

        return out;
    }
} // sqlite3