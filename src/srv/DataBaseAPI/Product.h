//
// Created by alpat on 15.04.2023.
//

#pragma once

#include "Object.h"
#include <string>


namespace DBAPI
{

	class Product : public Object
	{
		friend class DataBase;
	public:
		[[nodiscard]] std::string GetName() const;
		void SetName(const std::string& sNewName);

	private:
		explicit Product(uint64_t id);
	};

} // DBAPI
