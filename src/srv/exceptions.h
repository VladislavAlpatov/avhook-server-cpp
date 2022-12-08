//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <exception>



namespace server::exception
    {
        class RecvFailed  final : public std::exception
        {
        public:
            [[nodiscard]] const char *what() const override
            {
                return "server::recv function failed to get data from connection";
            }
        };
        class InvalidPacketSize final : public std::exception
        {
        public:
            [[nodiscard]] const char *what() const override
            {
                return "The size of the packet to be received is invalid";
            }
        };
    class InvalidPacketType final : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const override
        {
            return "The type of packet is invalid";
        }
    };
    class PacketFactoryNoAuthCreation final  : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const override
        {
            return "PacketFactory cant create Auth packet";
        }
    };
    class ClientNotRegistered final : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const override
        {
            return "Failed to get client id from not registered client";
        }
    };
}