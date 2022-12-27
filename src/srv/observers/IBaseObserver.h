//
// Created by nullifiedvlad on 27.12.2022.
//
#pragma once

namespace Observers
{
	class IBaseObserver
	{
	public:
		virtual void HandleEvent() = 0;
		virtual ~IBaseObserver() {};
	};
}