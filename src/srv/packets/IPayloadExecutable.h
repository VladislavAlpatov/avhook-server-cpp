//
// Created by Vladislav on 3/20/2023.
//

#pragma once
#include <nlohmann/json.hpp>

namespace web
{
    class ClientHandle;
    class IPayloadExecutable
    {
    public:
        virtual nlohmann::json ExecutePayload(ClientHandle &clientHandle) = 0;
        virtual  ~IPayloadExecutable() = default;
    };
}
