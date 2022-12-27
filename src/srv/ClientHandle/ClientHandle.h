//
// Created by nullifiedvlad on 27.12.2022.
//
#pragma once
#include <WinSock2.h>


namespace Web::ClientHandle
{
	void CreateNewThreadHandle(SOCKET clientSocket);
}