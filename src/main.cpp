//
// Created by Vlad on 04.12.2022.
//
#include "srv/server.h"
#include "srv/observers/OnUserConnected.h"
int main()
{
	const auto pServer = Web::Server::Get();
	pServer->AddObserver(new Observers::OnUserConnected());
}