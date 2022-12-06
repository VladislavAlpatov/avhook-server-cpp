//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <string>


namespace server::packet
{

    class Base
    {
    public:
        virtual std::string execute_payload() = 0;
    };

} // packet