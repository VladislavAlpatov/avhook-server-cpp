//
// Created by alpat on 14.02.2023.
//

#pragma once
#include "Object.h"
#include <nlohmann/json.hpp>


namespace DBAPI
{

    class Config final : public Object
    {
    public:
        Config(int iId);
        void SetData(const nlohmann::json& data);
        void GetData() const;

    };

} // DBAPI
