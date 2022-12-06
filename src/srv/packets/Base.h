//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <string>
#include "nlohmann/json.hpp"

namespace server
{
    class PacketFacory;
}
namespace server::packet
{

    class Base
    {
        friend class server::PacketFacory;
    public:
        virtual std::string execute_payload() = 0;

    protected:
        nlohmann::json m_Data;
        explicit Base(const nlohmann::json& data);
    };

} // packet