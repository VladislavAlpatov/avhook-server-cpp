//
// Created by nullifiedvlad on 27.12.2022.
//
#pragma once

class ObservableObject;

namespace observers
{
	class IBaseObserver
	{
	public:
		virtual void HandleEvent(const ObservableObject *pContext) = 0;
		virtual ~IBaseObserver() = default;
	};
}