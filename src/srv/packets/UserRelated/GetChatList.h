//
// Created by vladislav on 07.03.23.
//

#pragma once


#include "UserRelated.h"


namespace Web::Packet::User
{
    class GetChatList final : public UserRelated
    {
    public:
        explicit GetChatList(const nlohmann::json &data) : UserRelated(data) {};
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };

}
