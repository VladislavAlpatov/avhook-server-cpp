//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <nlohmann/json.hpp>
#include "IPayloadExecutable.h"
namespace web {class ClientHandle;}

namespace web::packet
{

    class BasePacket : public IPayloadExecutable
    {
    public:
        ~BasePacket() override = default;
    protected:
        nlohmann::json m_Data;
        BasePacket() = default;
        explicit BasePacket(const nlohmann::json& data);
    private:

    };

} // packet