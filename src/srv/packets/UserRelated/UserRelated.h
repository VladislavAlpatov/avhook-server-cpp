//
// Created by vladislav on 09.03.23.
//

#pragma once
#include "../BasePacket.h"
#include "../../DataBaseAPI/User.h"

namespace Web::Packet::Decorator
{
    class CantModifyOtherUsers;
}

namespace Web::Packet::User
{
    class UserRelated : public BasePacket
    {
    friend Decorator::CantModifyOtherUsers;

    public:
        explicit UserRelated(const nlohmann::json &data);
    protected:
        DBAPI::User m_pUserFromPacket;
    };
}
