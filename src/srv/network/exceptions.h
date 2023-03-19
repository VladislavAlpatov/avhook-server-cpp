#include <exception>

namespace Web::Network::Exception
{
    class RecvFailed final : public std::exception
    {
        [[nodiscard]] const char* what() const noexcept override
        {
            return "recv function failed";
        }

    };
    class SocketAcceptionFaild final : public std::exception
    {
        [[nodiscard]] const char* what() const noexcept override
        {
            return "Failed to accept new connection socket";
        }

    };
}