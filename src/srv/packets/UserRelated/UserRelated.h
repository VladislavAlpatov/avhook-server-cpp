//
// Created by vladislav on 09.03.23.
//

#pragma once
#include "../BasePacket.h"
#include "../../DataBaseAPI/User.h"

namespace Web::Packet::User
{
    class UserRelated : public BasePacket
    {
    public:
        explicit UserRelated(const nlohmann::json &data);
    protected:
        DBAPI::User m_userFromPacket;
    };
}
