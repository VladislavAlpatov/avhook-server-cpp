//
// Created by Vladislav on 28.03.2023.
//

#pragma once

#include "ConfigRelated.h"

namespace web::packet::config
{
    class GetData final : public ConfigRelated
    {
    public:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;

        explicit GetData(const nlohmann::json &data);
    };

}
