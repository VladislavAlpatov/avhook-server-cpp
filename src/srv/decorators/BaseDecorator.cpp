#include "BaseDecorator.h"


namespace Web::Packet::Decorator
{

    BaseDecorator::BaseDecorator(const std::shared_ptr<BasePacket> &pPacket)
    {
        m_pDecoratedPacket = pPacket;
    }

    nlohmann::json BaseDecorator::ExecutePayload(ClientHandle &clientHandle)
    {
        return m_pDecoratedPacket->ExecutePayload(clientHandle);
    }
}