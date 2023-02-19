//
// Created by Vlad on 19.02.2023.
//
#pragma once

#include "BasePacket.h"


namespace Web::Packet
{
    class DownloadFile : public BasePacket
    {
    public:
        explicit DownloadFile(const nlohmann::json &data);

    public:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
        std::string m_sFileName;
    };
} // Packet
