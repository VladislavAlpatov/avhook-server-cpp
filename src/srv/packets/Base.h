//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <string>
#include "nlohmann/json.hpp"

namespace server::packet
{

    class Base
    {
    public:
        virtual std::string execute_payload(int userId) = 0;

    protected:
        nlohmann::json m_Data;
        explicit Base(const nlohmann::json& data);
    };

} // packet