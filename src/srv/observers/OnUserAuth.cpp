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

		printf("[LOG] A new user (%s#%lu) has been authorized\n", pClientContext->m_dbUser.GetName().c_str(),
               pClientContext->m_dbUser.GetID());

	}
} // Observers