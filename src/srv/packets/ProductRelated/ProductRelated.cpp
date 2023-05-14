//
// Created by alpat on 23.04.2023.
//

#include "ProductRelated.h"
#include "../exceptions.h"
#include "../../DataBaseAPI/DataBase.h"

namespace web::packet::Product
{
	ProductRelated::ProductRelated(const nlohmann::json& data) : BasePacket(data)
	{
		try
		{
			m_productFromPacket = dbapi::DataBase::Get()->GetProductById(data["product_id"]);
		}
		catch (...)
		{
			throw Exception::CorruptedPacket();
		}
	}
}
