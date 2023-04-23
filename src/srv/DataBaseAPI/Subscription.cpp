//
// Created by alpat on 22.04.2023.
//

#include "Subscription.h"
#include "DataBase.h"
#include <fmt/format.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "User.h"
namespace DBAPI
{
	Subscription::Subscription(uint64_t id) : Object(id)
	{

	}

	bool Subscription::IsExpired() const
	{
		auto currentDate = std::time(nullptr);;

		return static_cast<long>(currentDate) >= GetEndDate();
	}

	long Subscription::GetEndDate() const
	{
		auto pDataBase = DBAPI::DataBase::Get();
		const auto data = pDataBase->Query(fmt::format("SELECT `expire_date` FROM `subscriptions` WHERE `id` = {}",m_iID));
		boost::posix_time::ptime pt = boost::posix_time::time_from_string(data[0][0]);
		time_t time = boost::posix_time::to_time_t(pt);

		return static_cast<long>(time);
	}

	User Subscription::GetUser()
	{
		auto pDataBase = DBAPI::DataBase::Get();
		const auto data = pDataBase->Query(fmt::format("SELECT `user_id` FROM `subscriptions` WHERE `id` = {}",m_iID));

		return pDataBase->GetUserById(std::stoull(data[0][0]));
	}

} // DBAPI