//
// Created by nullifiedvlad on 29.12.2022.
//
#include "OnUserAuth.h"
#include "../ClientHandle/ClientHandle.h"
#include <cstdio>
#include "../../lib/sqlite/connection.h"
#include <fmt/format.h>


namespace Observers
{
	void OnUserAuth::HandleEvent(const ObservableObject *pContext)
	{
		const auto pClientContext = dynamic_cast<const Web::ClientHandle*>(pContext);
		if (!pClientContext)
			return;

		const auto userName =
				sql::Connection::Get()->Query(fmt::format("SELECT `name` FROM `users` WHERE `id` = {}",
						pClientContext->m_iUserIdInDataBase))[0][0];

		printf("[LOG] A new user (%s#%d) has been authorized\n", userName.c_str(), pClientContext->m_iUserIdInDataBase);

	}
} // Observers