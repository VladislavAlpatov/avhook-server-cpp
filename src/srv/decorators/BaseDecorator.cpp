#include "BaseDecorator.h"


namespace Web::Packet::Decorator
{

    BaseDecorator::BaseDecorator(const std::shared_ptr<BasePacket> &pPacket)
    {
        m_pDecoratedPacket = std::shared_ptr<BasePacket>(pPacket);
    }

    nlohmann::json BaseDecorator::ExecutePayload(ClientHandle &clientHandle)
    {
        return nlohmann::json();
    }
}