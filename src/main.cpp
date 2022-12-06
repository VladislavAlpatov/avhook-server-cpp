//
// Created by Vlad on 04.12.2022.
//
#include <sqlite3.h>
#include <cstdio>
#include <Windows.h>
#include "srv/server.h"
#include "lib/sqlite/Connection.h"

int main()
{

        auto conn = sql::Connection(R"(C:\Users\Vlad\Desktop\db.db)");
        for (const auto& row : conn.query("SELECT * FROM `users`"))
        {
        for (const auto& str : row)
            printf("%s ", str.c_str());
        printf("\n");
    }

    server::Server::get()->listen();
}