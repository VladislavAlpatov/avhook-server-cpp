//
// Created by alpat on 15.04.2023.
//

#pragma once

#include "Object.h"
#include <string>


namespace dbapi
{

	class Product final : public Object
	{
		friend class DataBase;
	public:
		Product() = default;
		[[nodiscard]] std::string GetName() const;
		void SetName(const std::string& sNewName);

	private:
		Product(uint64_t id);
	};

} // dbapi
