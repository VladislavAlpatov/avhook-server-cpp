//
// Created by nullifiedvlad on 06.12.2022.
//
#pragma once
#include <exception>



namespace web::Exception
    {
    class InvalidPacketType final : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const noexcept override
        {
            return "The type of packet is invalid";
        }
    };
}