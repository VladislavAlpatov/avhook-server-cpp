//
// Created by Vladislav on 28.03.2023.
//

#pragma once
#include "../../DataBaseAPI/User.h"

// Inherit Web::IPayloadExecutable to resolve calling of wrong virtual method
class IUserAccessible
{
public:
    virtual DBAPI::User GetUser() = 0;
};