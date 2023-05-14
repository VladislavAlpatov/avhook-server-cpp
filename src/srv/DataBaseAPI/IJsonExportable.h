//
// Created by Vlad on 24.02.2023.
//

#pragma once
#include <nlohmann/json.hpp>


namespace dbapi
{

    class IJsonExportable
    {
    public:
        virtual nlohmann::json ToJson() const = 0;
    };

} // dbapi
