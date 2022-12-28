//
// Created by nullifiedvlad on 29.12.2022.
//
#pragma once
#include "IBaseObserver.h"


namespace Observers
{

	class OnPacket final : public IBaseObserver
	{
	public:
		void HandleEvent(const ObservableObject* pContext) override;
	};

} // Observers