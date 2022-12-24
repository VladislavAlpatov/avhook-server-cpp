#include <exception>

namespace nnl::exception
{
    class RecvFailed final : public std::exception
    {
        const char* what() const noexcept override
        {
            return "recv function faild";
        }

    };
}