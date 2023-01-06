//
// Created by Vlad on 04.12.2022.
//
#include "srv/server.h"
#include "srv/observers/OnServerStartup.h"
#if defined(_WIN32) and __has_include("winsock2.h")
#include <winsock.h>
#endif

int main()
{
#if defined(_WIN32) and __has_include("winsock2.h")
    WSAData data;
    int x = WSAStartup(MAKEWORD(2, 2), &data);
#endif
	const auto pServer = Web::Server::Get();
	pServer->AddObserver(new Observers::OnServerStartup());

	pServer->Listen();


}