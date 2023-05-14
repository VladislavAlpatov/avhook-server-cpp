//
// Created by Vladislav on 28.03.2023.
//

#pragma once
#include "../../DataBaseAPI/User.h"

// Inherit web::IPayloadExecutable to resolve calling of wrong virtual method
class IUserAccessible
{
public:
    virtual dbapi::User GetUser() = 0;
};