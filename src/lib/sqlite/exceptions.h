//
// Created by nullifiedvlad on 06.12.2022.
//
#include <exception>

namespace sql::exception
{
    class FailedConnectToDataBase : public std::exception
    {
    public:
        [[nodiscard]] const char *what() const override
        {
            return "Failed to open data base";
        }

    };
}