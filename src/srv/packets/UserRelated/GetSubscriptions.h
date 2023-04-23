//
// Created by alpat on 22.04.2023.
//

#pragma once
#include "UserRelated.h"

namespace Web::Packet::User
{
	class GetSubscriptions final : public UserRelated
	{
	public:
		explicit GetSubscriptions(const nlohmann::json& data);

		nlohmann::json ExecutePayload(ClientHandle& clientHandle) override;
	};
}
