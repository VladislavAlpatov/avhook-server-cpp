//
// Created by alpat on 23.04.2023.
//

#include "GetName.h"
namespace Web::Packet::Product
{
	GetName::GetName(const nlohmann::json& data) : ProductRelated(data)
	{
	}

	nlohmann::json GetName::ExecutePayload(ClientHandle& clientHandle)
	{
		return {{"name", m_productFromPacket.GetName()}};
	}
}