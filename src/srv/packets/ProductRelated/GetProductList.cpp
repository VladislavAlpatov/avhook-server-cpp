//
// Created by alpat on 23.04.2023.
//

#include "GetProductList.h"
#include "../../DataBaseAPI/DataBase.h"
#include "../../DataBaseAPI/Product.h"


namespace web::packet::Product
{
	nlohmann::json GetProductList::ExecutePayload(web::ClientHandle& clientHandle)
	{
		std::vector<nlohmann::json> out;

		for (const auto& product : dbapi::DataBase::Get()->GetProductList())
			out.push_back({{"id", product.GetID()}});

		return {{"products", out}};
	}

	GetProductList::GetProductList(const nlohmann::json& data) : BasePacket(data)
	{
	}
}