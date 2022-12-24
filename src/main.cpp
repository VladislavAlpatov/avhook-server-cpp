//
// Created by Vlad on 04.12.2022.
//
#include "srv/server.h"


int main()
{
    Web::Server::get()->listen();
}