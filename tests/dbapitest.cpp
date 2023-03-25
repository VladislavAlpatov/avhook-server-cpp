//
// Created by Vladislav on 25.03.2023.
//
#include <gtest/gtest.h>
#include "../src/srv/DataBaseAPI/DataBase.h"


// Demonstrate some basic assertions.
TEST(DBAPI, DataBaseSingletonInitialization)
{
    auto pDataBase = DBAPI::DataBase::Get();

    EXPECT_TRUE(pDataBase != nullptr);
}