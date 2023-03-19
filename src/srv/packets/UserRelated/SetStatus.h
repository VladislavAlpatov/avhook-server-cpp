//
// Created by Vladislav on 3/19/2023.
//

#pragma once
#include "UserRelated.h"

namespace Web::Packet::User
{
    class SetStatus final : public UserRelated
    {
    public:
        explicit SetStatus(const nlohmann::json &data);

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;

    private:
        std::string m_newStatus;
    };
}
