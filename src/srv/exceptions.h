//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <exception>



namespace Web::exception
    {
        class RecvFailed  final : public std::exception
        {
        public:
            [[nodiscard]] const char *what() const noexcept override
            {
                return "server::recv function failed";
            }
        };
        class InvalidPacketSize final : public std::exception
        {
        public:
            [[nodiscard]] const char *what() const noexcept override
            {
                return "The size of the packet is too large or its less than 1 byte";
            }
        };
    class InvalidPacketType final : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const noexcept override
        {
            return "The type of packet is invalid";
        }
    };
    class PacketFactoryNoAuthCreation final  : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const noexcept override
        {
            return "PacketFactory cant create Auth packet";
        }
    };
    class ClientNotRegistered final : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const noexcept override
        {
            return "Failed to get client id from not registered client";
        }
    };
}