//
// Created by vladislav on 08.03.23.
//

#pragma once
#include "UserRelated.h"

namespace Web::Packet::User
{
    class SetName final : public UserRelated
    {
    public:
        explicit SetName(const nlohmann::json &data);

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;

    private:
        std::string m_sNewUserName;
    };
}
