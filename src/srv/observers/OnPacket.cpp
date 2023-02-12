//
// Created by nullifiedvlad on 29.12.2022.
//
#include "OnPacket.h"
#include "../ClientHandle/ClientHandle.h"
#include "../DataBaseAPI/DataBase.h"
#include "../DataBaseAPI/User.h"

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

		const auto user = DBAPI::DataBase::Get()->GetUserById(pClientContext->m_iUserId);
		printf("[LOG] Accepted packet from (%s#%d)\n", user.GetName().c_str(), pClientContext->m_iUserId);
	}
} // Observers