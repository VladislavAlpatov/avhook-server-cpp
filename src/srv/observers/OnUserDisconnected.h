//
// Created by nullifiedvlad on 27.12.2022.
//
#pragma once
#include "IBaseObserver.h"

namespace Observers
{

	class OnUserDisconnected final : public IBaseObserver
	{
	public:
		void HandleEvent() override;
	};

} // Obsevers