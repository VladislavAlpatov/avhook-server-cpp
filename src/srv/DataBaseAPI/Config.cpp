//
// Created by alpat on 14.02.2023.
//

#include "Config.h"
#include "DataBase.h"
#include <string>
#include <boost/algorithm/string.hpp>
#include <fmt/format.h>


namespace DBAPI
{
    Config::Config(int iId)
    {
        m_iID = iId;
    }

    void Config::SetData(const nlohmann::json &data)
    {
        auto pDataBase = DBAPI::DataBase::Get();
        std::string jsnDump = data.dump();

        boost::replace_all(jsnDump, "'", "''");
        boost::replace_all(jsnDump, "\"", "\"\"");

        pDataBase->Query(fmt::format("UPDATE `configs` SET `data` '{}' WHERE `id` = {}", jsnDump, m_iID));
    }
    void Config::GetData() const
    {
        auto pDataBase = DBAPI::DataBase::Get();
        int x;
        pDataBase->Query(fmt::format("SELECT `data` FROM `configs` WHERE `id` = {}", m_iID));
    }
} // DBAPI