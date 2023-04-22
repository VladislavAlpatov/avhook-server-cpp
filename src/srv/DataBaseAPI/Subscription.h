//
// Created by alpat on 22.04.2023.
//

#pragma once
#include "Object.h"
#include <string>

namespace DBAPI
{

	class Subscription : public Object
	{
	public:
		explicit Subscription(uint64_t id);
		[[nodiscard]] std::string GetName() const;
		void SetName(std::string sNewName);
	};

} // DBAPI
