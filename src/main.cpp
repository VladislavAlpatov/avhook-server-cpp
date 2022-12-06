//
// Created by Vlad on 04.12.2022.
//
#include <cstdio>
#include <Windows.h>
#include "srv/server.h"
#include "lib/sqlite/connection.h"

int main()
{
    server::Server::get()->listen();
}