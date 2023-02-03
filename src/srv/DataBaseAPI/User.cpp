//
// Created by alpat on 03.02.2023.
//

#include "User.h"
#include "DataBase.h"
#include <fmt/format.h>

namespace DBAPI
{
    User::User(int iUserId)
    {
        m_iID = iUserId;
    }

    std::string User::GetName() const
    {
        auto pDataBase = DataBase::Get();
        return pDataBase->Query(fmt::format("SELECT `name` FROM `users` WHERE `id` = {}", m_iID))[0][0];
    }
} // DBAPI