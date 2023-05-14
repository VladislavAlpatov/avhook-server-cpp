//
// Created by alpat on 23.04.2023.
//

#pragma once
#include "../BasePacket.h"
#include "../../DataBaseAPI/Subscription.h"
#include "../interfaces/IUserAccessible.h"

namespace web::packet::subscription
{
	class SubscriptionRelated : public BasePacket, public IUserAccessible
	{
	public:
		explicit SubscriptionRelated(const nlohmann::json& data);

		dbapi::User GetUser() override;

	protected:
		dbapi::Subscription m_SubFromPacket;
	};
}
