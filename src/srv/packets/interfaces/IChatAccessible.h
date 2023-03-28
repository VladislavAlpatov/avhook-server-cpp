//
// Created by Vladislav on 3/20/2023.
//

#pragma once
#include "../../DataBaseAPI/Chat.h"

// Inherit Web::IPayloadExecutable to resolve calling of wrong virtual method
class IChatAccessible
{
public:
    virtual DBAPI::Chat GetChat() = 0;
};