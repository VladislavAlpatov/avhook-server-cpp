
enable_testing()

project(dbapi_test)
add_executable(dbapi_test dbapitest.cpp)


file(GLOB dbapitest_SRC "../src/srv/DataBaseAPI/*.cpp" "../src/lib/sqlite/*.cpp" "../src/lib/base64/*.cpp")


target_sources(dbapi_test PRIVATE ${dbapitest_SRC})
target_include_directories(dbapi_test PRIVATE ../src/srv/DataBaseAPI)

find_package(GTest REQUIRED)
target_link_libraries(dbapi_test PRIVATE GTest::GTest GTest::Main)
target_link_libraries(dbapi_test PRIVATE ${Boost_LIBRARIES})
target_link_libraries(dbapi_test PRIVATE SQLite::SQLite3)
target_link_libraries( dbapi_test PRIVATE nlohmann_json )
target_link_libraries(dbapi_test PRIVATE fmt::fmt)


gtest_discover_tests(dbapi_test)