//
// Created by alpat on 22.04.2023.
//

#include "GetSubscriptions.h"
#include "../../DataBaseAPI/Subscription.h"

namespace web::packet::user
{
	nlohmann::json GetSubscriptions::ExecutePayload(web::ClientHandle& clientHandle)
	{
		std::vector<nlohmann::json> subsJson;
		const auto subs = m_pUserFromPacket.GetSubscriptions();
		subsJson.reserve(subs.size());

		for (const auto sub : subs)
			subsJson.push_back({{"id", sub.GetID()}});

		return {{"subscriptions", subsJson}};
	}

	GetSubscriptions::GetSubscriptions(const nlohmann::json& data) : UserRelated(data)
	{
	}
}