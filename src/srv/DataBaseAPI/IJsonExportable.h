//
// Created by Vlad on 24.02.2023.
//

#pragma once
#include <nlohmann/json.hpp>


namespace DBAPI
{

    class IJsonExportable
    {
    public:
        virtual nlohmann::json ToJson() const = 0;
    };

} // DBAPI
