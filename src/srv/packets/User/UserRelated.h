//
// Created by vladislav on 09.03.23.
//

#pragma once
#include "../BasePacket.h"
#include "../../DataBaseAPI/User.h"

namespace web::packet::decorator
{
    class OwnerOnly;
}

namespace web::packet::user
{
    class UserRelated : public BasePacket
    {
    friend decorator::OwnerOnly;

    public:
        explicit UserRelated(const nlohmann::json &data);
    protected:
        dbapi::User m_pUserFromPacket;
    };
}
