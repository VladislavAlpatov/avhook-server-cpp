//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <nlohmann/json.hpp>

namespace Web {class ClientHandle;}

namespace Web::Packet
{

    class BasePacket
    {
    public:
        virtual ~BasePacket() = default;
        virtual nlohmann::json ExecutePayload(ClientHandle &clientHandle) = 0;
    protected:
        nlohmann::json m_Data;
        BasePacket() = default;
        explicit BasePacket(const nlohmann::json& data);
    private:

    };

} // packet