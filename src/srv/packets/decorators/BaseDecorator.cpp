#include "BaseDecorator.h"


namespace web::packet::decorator
{

    BaseDecorator::BaseDecorator(std::unique_ptr<IPayloadExecutable> &pPacket)
    {
        m_pDecoratedPacket = std::move(pPacket);
    }

    nlohmann::json BaseDecorator::ExecutePayload(ClientHandle &clientHandle)
    {
        return m_pDecoratedPacket->ExecutePayload(clientHandle);
    }
}