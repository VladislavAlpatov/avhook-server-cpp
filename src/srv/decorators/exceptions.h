//
// Created by alpat on 26.01.2023.
//
#pragma once
#include "../packets/exceptions.h"
namespace Web::Packet::Decorator::Exception
{
    class UserNotRegistered final : public Packet::Exception::BasePacketException
    {
    public:
        const char *what() const noexcept override
        {
            return "Access denied";
        }

    };
}