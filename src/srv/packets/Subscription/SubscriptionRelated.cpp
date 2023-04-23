//
// Created by alpat on 23.04.2023.
//

#include "SubscriptionRelated.h"
#include "../exceptions.h"
#include "../../DataBaseAPI/DataBase.h"
namespace Web::Packet::Subscription
{

	SubscriptionRelated::SubscriptionRelated(const nlohmann::json& data) : BasePacket(data)
	{
		try
		{
			m_SubFromPacket = DBAPI::DataBase::Get()->GetSubscriptionById(data.at("sub_id"));
		}
		catch (...)
		{
			throw Exception::CorruptedPacket();
		}
	}

	DBAPI::User SubscriptionRelated::GetUser()
	{
		return m_SubFromPacket.GetUser();
	}
}