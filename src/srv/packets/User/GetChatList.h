//
// Created by vladislav on 07.03.23.
//

#pragma once


#include "UserRelated.h"


namespace web::packet::user
{
    class GetChatList final : public UserRelated
    {
    public:
        explicit GetChatList(const nlohmann::json &data) : UserRelated(data) {};
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };

}
