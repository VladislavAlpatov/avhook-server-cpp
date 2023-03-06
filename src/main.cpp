//
// Created by Vlad on 04.12.2022.
//
#include "srv/server.h"
#include "srv/observers/OnServerStartup.h"
#include "srv/observers/OnUserConnected.h"
#include "srv/observers/OnUserDisconnected.h"
#include "lib/crypto/rsa.h"
#if defined(_WIN32) and __has_include("winsock2.h")
#include <winsock.h>
#endif

int main()
{
#if defined(_WIN32) and __has_include("winsock2.h")
    WSAData data;
    WSAStartup(MAKEWORD(2, 2), &data);
#endif
	const auto pServer = Web::Server::Get();

#ifdef _DEBUG
    setbuf(stdout, 0);

	pServer->AddObserver(new Observers::OnServerStartup());
    pServer->AddObserver(new Observers::OnUserDisconnected());
    pServer->AddObserver(new Observers::OnUserConnected());
#endif
	pServer->Listen();
}
