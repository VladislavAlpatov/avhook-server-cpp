//
// Created by vladislav on 07.03.23.
//

#pragma once


#include "../BasePacket.h"

namespace Web::Packet::User
{
    class GetChatList final : public BasePacket
    {
    public:
        explicit GetChatList(const nlohmann::json &data);

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;

    private:
        int m_iUserId = 0;
    };

}
