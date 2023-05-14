//
// Created by alpat on 15.04.2023.
//

#include "ActivationKey.h"
#include "DataBase.h"
#include "User.h"

#include <fmt/format.h>

namespace dbapi
{
	ActivationKey::ActivationKey(uint64_t id) : Object(id)
	{

	}

	uint64_t ActivationKey::GetkeyData() const
	{
		auto pDataBase = dbapi::DataBase::Get();

		const auto data = pDataBase->Query(fmt::format("SELECT `data` FROM `activation-keys` WHERE `id` = {}", m_iID));


		return std::stoull(data[0][0]);
	}

	bool ActivationKey::IsActivated() const
	{
		auto pDataBase = dbapi::DataBase::Get();

		const auto data = pDataBase->Query(fmt::format("SELECT `activated` FROM `activation-keys` WHERE `id` = {}", m_iID));

		return std::stoi(data[0][0]);
	}

	void ActivationKey::ActivateKey(User& user)
	{

	}

}