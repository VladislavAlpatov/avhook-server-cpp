//
// Created by Vlad on 04.12.2022.
//
#include "srv/server.h"
#include "srv/observers/OnServerStartup.h"
#include "srv/observers/OnUserConnected.h"
#include "srv/observers/OnUserDisconnected.h"
#include <openssl/rsa.h>
#include "lib/crypto/RSA.h"


int main()
{
#ifdef _DEBUG
	setbuf(stdout, 0);
#endif
	printf("[LOG] Generating RSA keys....\n");
	Encryption::RSA rsa(2048);
	const std::vector<uint8_t> data = {'h', 'e', 'l', 'l','o', '!'};
	auto encData = rsa.Encrypt(data);
	printf("[LOG] RSA done!\n");
	const auto pServer = Web::Server::Get();

#ifdef _DEBUG
	pServer->AddObserver(new Observers::OnServerStartup());
    pServer->AddObserver(new Observers::OnUserDisconnected());
    pServer->AddObserver(new Observers::OnUserConnected());
#endif
	pServer->Listen();
}
