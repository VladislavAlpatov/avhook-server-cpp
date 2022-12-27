//
// Created by nullifiedvlad on 27.12.2022.
//
#pragma once
#include <list>
#include <memory>
#include "observers/IBaseObserver.h"


class ObservableObject
{
public:
	void AddObserver(Observers::IBaseObserver* pObserver)
	{
		m_Observers.emplace_back(pObserver);
	}
protected:
	std::list<std::shared_ptr<Observers::IBaseObserver>> m_Observers;

	template<typename ObserverType>
	void NotifyObserver()
	{
		for (auto& pObserver : m_Observers)
			if (dynamic_cast<ObserverType*>(pObserver.get()))
				pObserver->HandleEvent();
	}
};
