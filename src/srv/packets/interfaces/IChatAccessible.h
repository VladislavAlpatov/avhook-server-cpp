//
// Created by Vladislav on 3/20/2023.
//

#pragma once
#include "../../DataBaseAPI/Chat.h"

// Inherit web::IPayloadExecutable to resolve calling of wrong virtual method
class IChatAccessible
{
public:
    virtual dbapi::Chat GetChat() = 0;
};