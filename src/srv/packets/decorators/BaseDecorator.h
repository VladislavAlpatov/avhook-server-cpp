//
// Created by alpat on 20.01.2023.
//
#pragma once
#include "../BasePacket.h"
#include "../../ClientHandle/ClientHandle.h"

#include <memory>
namespace web::packet::decorator
{
    class BaseDecorator : public IPayloadExecutable
    {
    public:
        explicit BaseDecorator(std::unique_ptr<IPayloadExecutable> &pPacket);
        BaseDecorator() = default;
        virtual ~BaseDecorator() = default;
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;

        template<class... Args>
        friend std::unique_ptr<IPayloadExecutable> MultipleDecoration(BasePacket* pPacket, Args... args);

    protected:
        std::unique_ptr<IPayloadExecutable> m_pDecoratedPacket;

        template<class Type>
        Type* GetOriginalPacket()
        {
            IPayloadExecutable* pPrevObj = m_pDecoratedPacket.get();

            while (true)
            {

                if(dynamic_cast<Type*>(pPrevObj))
                    return dynamic_cast<Type*>(pPrevObj);

                if (dynamic_cast<BaseDecorator*>(pPrevObj) == nullptr)
                    throw std::runtime_error("not found packet");

                pPrevObj = dynamic_cast<BaseDecorator*>(pPrevObj)->m_pDecoratedPacket.get();
            }
        }
    };

    template<class... Args>
    std::unique_ptr<IPayloadExecutable> MultipleDecoration(BasePacket* pPacket, Args... args)
    {
        const std::vector<BaseDecorator*> decorators = {args...};
        auto pDecoratedPacket =  std::unique_ptr<IPayloadExecutable>(pPacket);

        for (auto pDecorator : decorators)
        {
            pDecorator->m_pDecoratedPacket = std::move(pDecoratedPacket);
            pDecoratedPacket = std::move(std::unique_ptr<IPayloadExecutable>(pDecorator));
        }

        return pDecoratedPacket;
    }

}
