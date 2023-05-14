//
// Created by alpat on 14.02.2023.
//

#pragma once
#include "Object.h"
#include <nlohmann/json.hpp>


namespace dbapi
{
    class User;
    class Config final : public Object
    {
    public:
        Config() : Object() {};
        Config(uint64_t iId);
        void SetData(const nlohmann::json& data);
        [[nodiscard]] nlohmann::json GetData() const;
        [[nodiscard]] User GetOwner() const;

    };

} // dbapi
