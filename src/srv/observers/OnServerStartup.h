//
// Created by nullifiedvlad on 27.12.2022.
//
#pragma once
#include "IBaseObserver.h"
#include "ObservableObject.h"

namespace observers
{

	class OnServerStartup final : public IBaseObserver
	{
	public:
		void HandleEvent(const ObservableObject *pContext) override;
	};

} // observers