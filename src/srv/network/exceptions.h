#include <exception>

namespace web::network::Exception
{
    class RecvFailed final : public std::exception
    {
        [[nodiscard]] const char* what() const noexcept override
        {
            return "recv function failed";
        }

    };
    class SocketAcceptionFailed final : public std::exception
    {
        [[nodiscard]] const char* what() const noexcept override
        {
            return "Failed to accept new connection socket";
        }

    };
}