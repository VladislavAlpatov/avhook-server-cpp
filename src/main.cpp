//
// Created by Vlad on 04.12.2022.
//
#include "srv/server.h"


int main()
{
    server::Server::get()->listen();
}