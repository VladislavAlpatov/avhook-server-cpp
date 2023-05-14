//
// Created by alpat on 26.01.2023.
//
#pragma once
#include "../exceptions.h"
namespace web::packet::decorator::Exception
{
    class UserNotRegistered final : public packet::Exception::BasePacketException
    {
    public:
        const char *what() const noexcept override
        {
            return "Access denied";
        }

    };
}