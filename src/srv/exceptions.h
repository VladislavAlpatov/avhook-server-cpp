//
// Created by nullifiedvlad on 06.12.2022.
//
#include <exception>



namespace server::exception
    {
        class RecvFailed : public std::exception
        {
        public:
            [[nodiscard]] const char *what() const override
            {
                return "server::recv function failed to get data from connection";
            }
        };
        class InvalidPacketSize : public std::exception
        {
        public:
            [[nodiscard]] const char *what() const override
            {
                return "The size of the packet to be received is invalid";
            }
        };
    class InvalidPacketType : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const override
        {
            return "The type of packet is invalid";
        }
    };
    }