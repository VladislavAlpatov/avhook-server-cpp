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
		std::string GetName() const;
	};

} // DBAPI
