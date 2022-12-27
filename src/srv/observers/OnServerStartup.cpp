//
// Created by nullifiedvlad on 27.12.2022.
//
#include "OnServerStartup.h"
#include <cstdio>
namespace Observers
{
	void OnServerStartup::HandleEvent()
	{
		printf("[LOG] Server online, listening...");
	}
} // Observers