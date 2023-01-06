#include <exception>

namespace Web::Network::Exception
{
    class RecvFailed final : public std::exception
    {
        const char* what() const noexcept override
        {
            return "recv function faild";
        }

    };
    class SocketAcceptionFaild final : public std::exception
    {
        const char* what() const noexcept override
        {
            return "Failed to accept new connection socket";
        }

    };
}