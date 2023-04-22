//
// Created by alpat on 22.04.2023.
//

#include "Subscription.h"
#include "DataBase.h"
#include <fmt/format.h>
#include <chrono>


namespace DBAPI
{
	Subscription::Subscription(uint64_t id) : Object(id)
	{

	}

	bool Subscription::IsExpired() const
	{
		auto currentDate = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		return currentDate >= GetEndDate();
	}

	long Subscription::GetEndDate() const
	{
		auto pDataBase = DBAPI::DataBase::Get();
		const auto data = pDataBase->Query(fmt::format("SELECT `expire_date` FROM `subscriptions` WHERE `id` = {}",m_iID));

		return std::stol(data[0][0]);
	}
} // DBAPI