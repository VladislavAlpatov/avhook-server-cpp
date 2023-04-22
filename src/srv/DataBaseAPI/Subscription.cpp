//
// Created by alpat on 22.04.2023.
//

#include "Subscription.h"
#include "DataBase.h"
#include <fmt/format.h>
#include <boost/algorithm/string.hpp>
#include <chrono>


namespace DBAPI
{
	Subscription::Subscription(uint64_t id) : Object(id)
	{

	}

	std::string Subscription::GetName() const
	{
		auto pDataBase = DBAPI::DataBase::Get();

		const auto data = pDataBase->Query(fmt::format("SELECT `name` FROM `products` WHERE `id` = {}", m_iID));

		return data[0][0];
	}

	void Subscription::SetName(std::string sNewName)
	{
		auto pDataBase = DBAPI::DataBase::Get();
		boost::replace_all(sNewName, "'", "''");

		pDataBase->Query(fmt::format("UPDATE `products` SET `name` = '{}' WHERE `id` = {}",sNewName, m_iID));
	}

	bool Subscription::IsExpired() const
	{
		auto currentDate = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

		return currentDate >= GetEndDate();
	}

	long Subscription::GetEndDate() const
	{
		auto pDataBase = DBAPI::DataBase::Get();
		const auto data = pDataBase->Query(fmt::format("SELECT `expire_date` WHERE `id` = {}",m_iID));

		return std::stol(data[0][0]);
	}
} // DBAPI