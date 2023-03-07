//
// Created by nullifiedvlad on 08.12.2022.
//
#pragma once
#include <stdexcept>

namespace Web::Packet::Exception
{
    class BasePacketException : public std::exception
    {

    };
    class AuthFailedWrongPassword final : public BasePacketException
    {
    public:
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Client auth was failed, wrong password";
        }
    };
    class CorruptedPacket final  : public BasePacketException
    {
    public:
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Accepted package was corrupted";
        }
    };
    class InValidUserName final : public BasePacketException
    {
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Invalid username, it must not contain newlines or tabs";
        }
    };
    class UserInfoNotFound final  : public BasePacketException
    {
    public:
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Information about this user does not exist";
        }
    };
    class ConfigNotFound final : public BasePacketException
    {
    public:
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Failed to find avhook config";
        }
    };
    class ExceptedAutPacket final : public BasePacketException
    {
    public:
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Expected Auth packet";
        }
    };
    class ChatDoesNotExist final : public BasePacketException
    {
    public:
        const char *what() const noexcept override
        {
            return "Chat with this id does not exist";
        }
    };
    class UserNotRegistered final : public BasePacketException
    {
    public:
        const char *what() const noexcept override
        {
            return "Access denied";
        }
    };
}