#pragma once
#include "BasePacket.h"
namespace Web::Packet
{
    class DeleteChat final : public BasePacket
    {
    public:
        explicit DeleteChat(const nlohmann::json &data);
    private:
        int m_iChatId;
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    };
} // namespace Web::Packet
