//
// Created by alpat on 23.04.2023.
//

#pragma once
#include "../BasePacket.h"
#include "../../DataBaseAPI/Subscription.h"
#include "../interfaces/IUserAccessible.h"

namespace Web::Packet::Subscription
{
	class SubscriptionRelated : public BasePacket, public IUserAccessible
	{
	public:
		explicit SubscriptionRelated(const nlohmann::json& data);

		DBAPI::User GetUser() override;

	protected:
		DBAPI::Subscription m_SubFromPacket;
	};
}
