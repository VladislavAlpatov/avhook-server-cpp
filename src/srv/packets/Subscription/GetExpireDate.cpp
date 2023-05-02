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
		const auto pt        = boost::posix_time::from_time_t(m_SubFromPacket.GetEndDate());
		const auto timeFacet = new boost::posix_time::time_facet("%Y-%m-%d %H:%M:%S");
		std::stringstream ss;
		ss.imbue(std::locale(std::locale::classic(), timeFacet));
		ss << pt;
		return {{ "expire_date", ss.str()}};
	}
}