//
// Created by Vlad on 04.12.2022.
//
#include "srv/server.h"
#include "srv/observers/OnServerStartup.h"
#include "srv/observers/OnUserConnected.h"
#include "srv/observers/OnUserDisconnected.h"


int main()
{
#ifdef _DEBUG
	setbuf(stdout, 0);
#endif
	const auto pServer = web::Server::Get();
#ifdef _DEBUG
	pServer->AddObserver(new Observers::OnServerStartup());
    pServer->AddObserver(new Observers::OnUserDisconnected());
    pServer->AddObserver(new Observers::OnUserConnected());
#endif
	pServer->Listen();
}
