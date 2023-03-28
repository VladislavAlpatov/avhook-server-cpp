//
// Created by Vladislav on 28.03.2023.
//

#include "GetData.h"


namespace Web::Packet::Config
{
    GetData::GetData(const nlohmann::json &data) : ConfigRelated(data)
    {

    }

    nlohmann::json GetData::ExecutePayload(ClientHandle &clientHandle)
    {
        return {{"data", m_configFromPacket.GetData()}};
    }

}
