//
// Created by vladislav on 09.03.23.
//

#pragma once
#include "../BasePacket.h"
#include "../../DataBaseAPI/User.h"
#include "../interfaces/IUserAccessible.h"
namespace web::packet::decorator
{
    class OwnerOnly;
}

namespace web::packet::user
{
    class UserRelated : public BasePacket, public IUserAccessible
    {
    friend decorator::OwnerOnly;

    public:
        explicit UserRelated(const nlohmann::json &data);
        dbapi::User GetUser() override;
    protected:
        dbapi::User m_pUserFromPacket;
    };
}
