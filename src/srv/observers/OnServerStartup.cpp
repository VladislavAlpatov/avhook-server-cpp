//
// Created by nullifiedvlad on 27.12.2022.
//
#include "OnServerStartup.h"
#include "ObservableObject.h"
#include <cstdio>
#include <any>

namespace observers
{
	void OnServerStartup::HandleEvent(const ObservableObject *pContext)
	{
		printf("[LOG] Server online, listening...\n");
	}
} // observers