//
// Created by alpat on 22.04.2023.
//

#pragma once
#include "Object.h"
#include <string>

namespace DBAPI
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
		[[nodiscard]] User GetUser();
		[[nodiscard]] uint64_t GetUserId() const;
		[[nodiscard]] std::string GetExpireDateAsString() const;
	private:
		Subscription(uint64_t id);
	};

} // DBAPI
