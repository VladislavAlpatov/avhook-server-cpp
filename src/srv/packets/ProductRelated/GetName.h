//
// Created by alpat on 23.04.2023.
//

#pragma once
#include "ProductRelated.h"

namespace web::packet::Product
{
	class GetName final : public ProductRelated
	{
	public:
		explicit GetName(const nlohmann::json& data);

		nlohmann::json ExecutePayload(ClientHandle& clientHandle) override;
	};
}

