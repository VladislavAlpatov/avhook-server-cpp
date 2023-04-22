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
		friend class DataBase;
	public:
		Subscription(uint64_t id);
		[[nodiscard]] bool IsExpired() const;
		[[nodiscard]] long GetEndDate() const;
	};

} // DBAPI
