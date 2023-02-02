#pragma once
#include "BasePacket.h"

namespace Web::Packet
{
    class GetChatList final : public BasePacket
    {
    public:
        explicit GetChatList(const nlohmann::json &data);

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;

    public:

    };
}