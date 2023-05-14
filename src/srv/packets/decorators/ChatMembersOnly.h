//
// Created by Vladislav on 3/18/2023.
//

#pragma once
#include "BaseDecorator.h"


namespace web::packet::decorator
{
    class ChatMembersOnly final : public BaseDecorator
    {
    public:
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };

}
