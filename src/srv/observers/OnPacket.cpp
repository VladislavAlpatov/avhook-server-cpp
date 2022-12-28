//
// Created by nullifiedvlad on 29.12.2022.
//
#include "OnPacket.h"
#include <cstdio>
#include <fmt/format.h>
#include "../ClientHandle/ClientHandle.h"
#include "../../lib/sqlite/connection.h"

namespace Observers
{
	void OnPacket::HandleEvent(const ObservableObject* pContext)
	{
		const auto pClientContext = dynamic_cast<const Web::ClientHandle*>(pContext);
		if (!pClientContext) return;

		const auto userName =
				sql::Connection::Get()->Query(fmt::format("SELECT `name` FROM `users` WHERE `id` = {}",
						pClientContext->m_iUserIdInDataBase))[0][0];

		printf("[LOG] Accepted packet from (%s#%d)\n", userName.c_str(), pClientContext->m_iUserIdInDataBase);
	}
} // Observers