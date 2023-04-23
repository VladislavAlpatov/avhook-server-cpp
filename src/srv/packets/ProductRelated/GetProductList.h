//
// Created by alpat on 23.04.2023.
//

#pragma once
#include "../BasePacket.h"


namespace Web::Packet::Product
{
	class GetProductList final : public BasePacket
	{
	public:
		explicit GetProductList(const nlohmann::json& data);

	public:
		nlohmann::json ExecutePayload(ClientHandle& clientHandle) override;
	};
}
