//
// Created by alpat on 23.04.2023.
//

#include "CheckExpiration.h"


namespace web::packet::subscription
{
	CheckExpiration::CheckExpiration(const nlohmann::json& data) : SubscriptionRelated(data)
	{

	}

	nlohmann::json CheckExpiration::ExecutePayload(ClientHandle& clientHandle)
	{
		return {{"is_expired", m_SubFromPacket.IsExpired()}};
	}
}
