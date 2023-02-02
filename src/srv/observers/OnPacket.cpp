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
	void OnPacket::HandleEvent(const ObservableObject *pContext)
	{
		const auto pClientContext = dynamic_cast<const Web::ClientHandle*>(pContext);
		if (!pClientContext) return;
        if (pClientContext->m_iUserId == INVALID_USER_ID)
        {
            printf("[LOG] Accepted packet from unknow user\n");
            return;
        }
		const auto userName =
				sql::Connection::Get()->Query(fmt::format("SELECT `name` FROM `users` WHERE `id` = {}",
						pClientContext->m_iUserId))[0][0];

		printf("[LOG] Accepted packet from (%s#%d)\n", userName.c_str(), pClientContext->m_iUserId);
	}
} // Observers