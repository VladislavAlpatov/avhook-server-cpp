//
// Created by alpat on 15.04.2023.
//

#include "Product.h"
#include "DataBase.h"
#include <fmt/format.h>


namespace DBAPI
{
	Product::Product(uint64_t id) : Object(id)
	{
	}

	void Product::SetName(const std::string& sNewName)
	{

	}

	std::string Product::GetName() const
	{
		const auto data = DataBase::Get()->Query(fmt::format("SELECT `name` FROM `products` WHERE `id` = {}", m_iID));

		return data[0][0];
	}
} // DBAPI