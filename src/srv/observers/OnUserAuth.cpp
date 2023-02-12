//
// Created by nullifiedvlad on 29.12.2022.
//
#include "OnUserAuth.h"
#include "../ClientHandle/ClientHandle.h"
#include <cstdio>
#include "../DataBaseAPI/DataBase.h"
#include "../DataBaseAPI/User.h"
#include <fmt/format.h>


namespace Observers
{
	void OnUserAuth::HandleEvent(const ObservableObject *pContext)
	{
		const auto pClientContext = dynamic_cast<const Web::ClientHandle*>(pContext);
		if (!pClientContext)
			return;

		const auto user = DBAPI::DataBase::Get()->GetUserById(pClientContext->m_iUserId);

		printf("[LOG] A new user (%s#%d) has been authorized\n", user.GetName().c_str(), pClientContext->m_iUserId);

	}
} // Observers