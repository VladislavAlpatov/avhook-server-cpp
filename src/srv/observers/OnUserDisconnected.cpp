//
// Created by nullifiedvlad on 27.12.2022.
//

#include "OnUserDisconnected.h"
#include <cstdio>
namespace Observers
{
	void OnUserDisconnected::HandleEvent()
	{
		printf("[LOG] User Disconnected");
	}
} // Obsevers