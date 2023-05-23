//
// Created by nullifiedvlad on 27.12.2022.
//
#include "OnUserConnected.h"
#include <cstdio>
#include <any>

namespace observers
{
	void OnUserConnected::HandleEvent(const ObservableObject *pContext)
	{
		printf("[LOG] Connected new user\n");
	}
} // observers