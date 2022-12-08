//
// Created by nullifiedvlad on 08.12.2022.
//
#pragma once
#include "Base.h"
#define  PACKET_AUTH 1
namespace server::packet
{

    class Auth final : public Base
    {
    public:
        explicit Auth(const nlohmann::json &data);

    public:
        std::string execute_payload(int userId) override;


    };

} // packet