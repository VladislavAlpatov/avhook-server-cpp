//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <string>
#include "nlohmann/json.hpp"

namespace Web {class ClientHandle;}

#define FLAG_PACKET_ENCRYPTED_IN  (1<<0)
#define FLAG_PACKET_ENCRYPTED_OUT (1<<1)
#define FLAG_PACKET_RAW_DATA      (1<<2)


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
    };

} // packet