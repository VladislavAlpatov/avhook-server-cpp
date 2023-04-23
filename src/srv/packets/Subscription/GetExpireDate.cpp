//
// Created by alpat on 23.04.2023.
//

#include "GetExpireDate.h"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace Web::Packet::Subscription
{
	GetExpireDate::GetExpireDate(const nlohmann::json& data) : SubscriptionRelated(data)
	{
	}

	nlohmann::json GetExpireDate::ExecutePayload(ClientHandle& clientHandle)
	{
		boost::posix_time::ptime pt = boost::posix_time::from_time_t(m_SubFromPacket.GetEndDate());

		return {{ "expire_date", boost::posix_time::to_simple_string(pt)}};
	}
}