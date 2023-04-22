//
// Created by alpat on 22.04.2023.
//

#pragma once
#include "Object.h"
#include <string>

namespace DBAPI
{
	class Subscription final : public Object
	{
		friend class DataBase;
		friend class User;
	public:
		[[nodiscard]] bool IsExpired() const;
		[[nodiscard]] long GetEndDate() const;
	private:
		Subscription(uint64_t id);
	};

} // DBAPI
