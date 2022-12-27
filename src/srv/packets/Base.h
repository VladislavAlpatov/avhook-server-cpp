//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <string>
#include "nlohmann/json.hpp"

namespace Web::Packet
{

    class Base
    {
    public:
        virtual nlohmann::json ExecutePayload(int userId) = 0;

    protected:
        nlohmann::json m_Data;
        explicit Base(const nlohmann::json& data);
    };

} // packet