//
// Created by nullifiedvlad on 06.12.2022.
//
#include "connection.h"
#include "exceptions.h"
namespace sql
{
    Connection::Connection(const std::string &path)
    {
        if (sqlite3_open(path.c_str(), &m_pDataBase) != SQLITE_OK)
            throw exception::FailedConnectToDataBase();
    }

    std::vector<std::vector<std::string>> Connection::query(const std::string &str)
    {
        std::vector<std::vector<std::string>> out;

        sqlite3_stmt* pSqliteStatement = nullptr;

        std::lock_guard lock(m_lock);

        sqlite3_prepare_v2(m_pDataBase, str.c_str(), str.size(), &pSqliteStatement, nullptr);

        while (sqlite3_step(pSqliteStatement) != SQLITE_DONE)
        {
            const auto rowLength = sqlite3_column_count(pSqliteStatement);
            std::vector<std::string> rowData;
            rowData.reserve(rowLength);

            for (int i =0; i < rowLength; ++i)
            {
                const auto pText = sqlite3_column_text(pSqliteStatement, i);

                if (sqlite3_column_type(pSqliteStatement, i) != SQLITE_BLOB or !pText)
                    rowData.emplace_back((pText) ? (const char*)pText : "");
            }
            out.emplace_back(rowData);
        }
        sqlite3_finalize(pSqliteStatement);
        return out;
    }

    Connection::Connection(Connection && other) noexcept
    {
        std::swap(m_pDataBase, other.m_pDataBase);
    }

    Connection &Connection::operator=(Connection &&other) noexcept
    {
        if (&other == this)
            return *this;

        std::swap(m_pDataBase, other.m_pDataBase);

        return *this;
    }

    Connection::~Connection()
    {
        if (m_pDataBase)
            sqlite3_close(m_pDataBase);
    }

} // sqlite3