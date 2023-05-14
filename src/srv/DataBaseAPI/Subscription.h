//
// Created by alpat on 22.04.2023.
//

#pragma once
#include "Object.h"
#include <string>

namespace dbapi
{
	class User;
	class Subscription final : public Object
	{
		friend class DataBase;
		friend class User;

	public:
		Subscription() = default;

		[[nodiscard]] bool IsExpired() const;
		[[nodiscard]] long GetEndDate() const;
		[[nodiscard]] User GetUser() const;
		[[nodiscard]] uint64_t GetUserId() const;
	private:
		Subscription(uint64_t id);
	};

} // dbapi
