//
// Created by Vladislav on 25.03.2023.
//
#include <gtest/gtest.h>
#include <DataBase.h>
#include <User.h>


#define USER_ID_FOR_TESTS 1


DBAPI::DataBase* pDataBase = nullptr;

TEST(DBAPI, SingletonInitialization)
{
    pDataBase = DBAPI::DataBase::Get();

    EXPECT_TRUE(pDataBase != nullptr);
}
TEST(DBAPI, FindUserById)
{
    auto foundUser = pDataBase->GetUserById(USER_ID_FOR_TESTS);

    EXPECT_TRUE(foundUser.GetID() == USER_ID_FOR_TESTS);
}
TEST(DBAPI, GetUserName)
{
    EXPECT_NO_THROW(pDataBase->GetUserById(USER_ID_FOR_TESTS).GetName());
}

TEST(DBAPI, DBAPI_FindUserById_Test)
{

}