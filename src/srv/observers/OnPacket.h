//
// Created by nullifiedvlad on 29.12.2022.
//
#pragma once
#include "IBaseObserver.h"


namespace observers
{

	class OnPacket final : public IBaseObserver
	{
	public:
		void HandleEvent(const ObservableObject *pContext) override;
	};

} // observers