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
        explicit BaseDecorator(std::unique_ptr<BasePacket> &pPacket);
        BaseDecorator() = default;
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;

        template<class... Args>
        friend std::unique_ptr<BasePacket> MutipleDecoration(BasePacket* pPacket, Args... args);

    protected:
        std::unique_ptr<BasePacket> m_pDecoratedPacket;
    };

    template<class... Args>
    std::unique_ptr<BasePacket> MutipleDecoration(BasePacket* pPacket, Args... args)
    {
        const std::vector<BaseDecorator*> decorators = {args...};
        auto pDecoratedPacket =  std::unique_ptr<BasePacket>(pPacket);

        for (auto pDecorator : decorators)
        {
            pDecorator->m_pDecoratedPacket = std::move(pDecoratedPacket);
            pDecoratedPacket = std::move(std::unique_ptr<BasePacket>(pDecorator));
        }

        return pDecoratedPacket;
    }
}
