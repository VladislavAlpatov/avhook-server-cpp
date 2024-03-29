//
// Created by nullifiedvlad on 27.12.2022.
//
#pragma once
#include <list>
#include <memory>
#include "IBaseObserver.h"


class ObservableObject
{
	friend observers::IBaseObserver;
public:
	void AddObserver(observers::IBaseObserver* pObserver)
	{
		m_Observers.emplace_back(pObserver);
	}
	virtual ~ObservableObject() = default;
protected:
	std::list<std::shared_ptr<observers::IBaseObserver>> m_Observers;

	template<typename ObserverType>
	void NotifyObserver() const
	{
		for (auto& pObserver : m_Observers)
			if (dynamic_cast<ObserverType*>(pObserver.get()))
				pObserver->HandleEvent(this);
	}
};
