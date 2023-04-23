//
// Created by alpat on 23.04.2023.
//

#include "GetProductList.h"
#include "../../DataBaseAPI/DataBase.h"
#include "../../DataBaseAPI/Product.h"


namespace Web::Packet::Product
{
	nlohmann::json GetProductList::ExecutePayload(Web::ClientHandle& clientHandle)
	{
		std::vector<nlohmann::json> out;

		for (const auto& product : DBAPI::DataBase::Get()->GetProductList())
			out.push_back({{"id", product.GetID()}});

		return {{"products", out}};
	}

	GetProductList::GetProductList(const nlohmann::json& data) : BasePacket(data)
	{
	}
}