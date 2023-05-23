//
// Created by Vlad on 04.12.2022.
//
#include "srv/server.h"
#include "srv/observers/OnServerStartup.h"
#include "srv/observers/OnUserConnected.h"
#include "srv/observers/OnUserDisconnected.h"


int main()
{
    try
    {
#ifdef _DEBUG
        setbuf(stdout, 0);
#endif
        const auto pServer = web::Server::Get();

#ifdef _DEBUG
        pServer->AddObserver(new observers::OnServerStartup());
        pServer->AddObserver(new observers::OnUserDisconnected());
        pServer->AddObserver(new observers::OnUserConnected());
#endif
        pServer->Listen();
    }
    catch (const std::exception& ex)
    {
        printf("[FATAL ERROR] %s\n", ex.what());
        exit(-1);
    }
}
