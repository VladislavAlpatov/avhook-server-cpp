//
// Created by vladislav on 08.03.23.
//

#pragma once
#include "UserRelated.h"
#include "../interfaces/IUserAccessible.h"


namespace web::packet::user
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
