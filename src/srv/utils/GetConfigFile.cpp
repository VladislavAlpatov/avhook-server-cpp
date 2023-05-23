//
// Created by vlad on 23.05.23.
//

#include "GetConfigFile.h"
#include <fstream>


namespace utils
{
    nlohmann::json GetConfigFile()
    {
        auto configFile = std::fstream("config.json", std::ios::in);
        std::string configFileText(std::istreambuf_iterator<char>(configFile), {});

        return nlohmann::json::parse(configFileText);
    }
}