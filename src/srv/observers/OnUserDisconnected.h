//
// Created by nullifiedvlad on 27.12.2022.
//
#pragma once

#include <any>
#include "IBaseObserver.h"
#include "ObservableObject.h"

namespace Observers
{

	class OnUserDisconnected final : public IBaseObserver
	{
	public:
		void HandleEvent(const ObservableObject *pContext) override;
	};

} // Obsevers