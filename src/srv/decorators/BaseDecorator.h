//
// Created by alpat on 20.01.2023.
//
#pragma once
#include "../packets/BasePacket.h"
#include "../ClientHandle/ClientHandle.h"

#include <memory>
namespace Web::Packet::Decorator
{
    class BaseDecorator : public BasePacket
    {
    public:
        explicit BaseDecorator(const std::shared_ptr<BasePacket> &pPacket);

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;

    protected:
        std::shared_ptr<BasePacket> m_pDecoratedPacket;
    };
}
