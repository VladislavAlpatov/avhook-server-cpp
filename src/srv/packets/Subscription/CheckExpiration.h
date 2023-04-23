//
// Created by alpat on 23.04.2023.
//

#pragma once
#include "SubscriptionRelated.h"

namespace Web::Packet::Subscription
{
	class CheckExpiration final : public SubscriptionRelated
	{
	public:
		explicit CheckExpiration(const nlohmann::json& data);

		nlohmann::json ExecutePayload(ClientHandle& clientHandle) override;
	};

}
