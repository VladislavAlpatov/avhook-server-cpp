//
// Created by nullifiedvlad on 27.12.2022.
//
#include "OnUserConnected.h"
#include <cstdio>

namespace Observers
{
	void OnUserConnected::HandleEvent()
	{
		printf("[LOG] Connected new user");
	}
} // Observers