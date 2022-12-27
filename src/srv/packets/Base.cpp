//
// Created by nullifiedvlad on 06.12.2022.
//
#include "Base.h"

namespace Web::Packet
{

    Base::Base(const nlohmann::json&data)
    {
        m_Data = data;
    }
}// packet