//
// Created by alpat on 15.04.2023.
//

#pragma once
#include "Object.h"


namespace DBAPI
{
	class ActivationKey final : public Object
	{
	public:
		explicit ActivationKey(uint64_t id);
		// GetProduct() const;
		[[nodiscard]] uint64_t GetkeyData() const;
		[[nodiscard]] bool IsActivated() const;

	};

}
