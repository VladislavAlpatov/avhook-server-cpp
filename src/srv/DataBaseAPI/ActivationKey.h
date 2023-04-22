//
// Created by alpat on 15.04.2023.
//

#pragma once
#include "Object.h"


namespace DBAPI
{
	class User;
	class ActivationKey final : public Object
	{
	public:
		ActivationKey(uint64_t id);
		// GetProduct() const;
		[[nodiscard]] uint64_t GetkeyData() const;
		[[nodiscard]] bool IsActivated() const;
		[[nodiscard]] void ActivateKey(User& user);

	};

}
