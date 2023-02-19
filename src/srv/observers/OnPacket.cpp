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


        if (!pClientContext->m_dbUser.IsValid())
        {
            printf("[LOG] Accepted packet from unknow user\n");
            return;
        }
		printf("[LOG] Accepted packet from (%s#%d)\n",
               pClientContext->m_dbUser.GetName().c_str(),
               pClientContext->m_dbUser.GetID());
	}
} // Observers