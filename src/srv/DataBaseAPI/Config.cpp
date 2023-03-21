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
    Config::Config(uint64_t iId) : Object(iId)
    {

    }
    void Config::SetData(const nlohmann::json &data)
    {
        auto pDataBase = DBAPI::DataBase::Get();
        std::string jsnDump = data.dump();

        pDataBase->Query(fmt::format("UPDATE `configs` SET `data` = '{}' WHERE `id` = {}", jsnDump, m_iID));
    }
    nlohmann::json Config::GetData() const
    {
        auto pDataBase = DBAPI::DataBase::Get();
        const auto data = pDataBase->Query(fmt::format("SELECT `data` FROM `configs` WHERE `id` = {}", m_iID));

        return nlohmann::json::parse(data[0][0]);
    }
} // DBAPI