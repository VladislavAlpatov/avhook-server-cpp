//
// Created by Vlad on 04.12.2022.
//
#include "srv/server.h"
#include "srv/observers/OnServerStartup.h"

int main()
{
	const auto pServer = Web::Server::Get();
	pServer->AddObserver(new Observers::OnServerStartup());

	pServer->Listen();
}