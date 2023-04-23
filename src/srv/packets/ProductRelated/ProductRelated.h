//
// Created by alpat on 23.04.2023.
//

#pragma once
#include "../BasePacket.h"
#include "../../DataBaseAPI/Product.h"

namespace Web::Packet::Product
{
	class ProductRelated : public BasePacket
	{
	public:
		explicit ProductRelated(const nlohmann::json& data);
	protected:
		DBAPI::Product m_productFromPacket;
	};
}

