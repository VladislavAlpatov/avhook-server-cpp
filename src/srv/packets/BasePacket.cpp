//
// Created by nullifiedvlad on 06.12.2022.
//
#include "BasePacket.h"
namespace Web::Packet
{

    BasePacket::BasePacket(const nlohmann::json&data)
    {
        m_Data = data;
    }
}// packet