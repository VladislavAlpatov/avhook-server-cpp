
enable_testing()

project(dbapi_test)
add_executable(dbapi_test dbapitest.cpp)


file(GLOB dbapitest_SRC "../src/srv/DataBaseAPI/*.cpp" "../src/lib/sqlite/*.cpp" "../src/lib/base64/*.cpp")
file(GLOB dbapitest_HEADERS "../src/srv/DataBaseAPI/*.h")

target_sources(dbapi_test PRIVATE ${dbapitest_SRC})
target_include_directories(dbapi_test PRIVATE ${dbapitest_HEADERS})

find_package(GTest REQUIRED)
target_link_libraries(dbapi_test      PRIVATE GTest::GTest GTest::Main)
target_link_libraries(dbapi_test PRIVATE ${Boost_LIBRARIES})
target_link_libraries(dbapi_test PRIVATE SQLite::SQLite3)
target_link_libraries( dbapi_test PRIVATE nlohmann_json )
target_link_libraries(dbapi_test PRIVATE fmt::fmt)
target_link_libraries(dbapi_test PRIVATE OpenSSL::Crypto)


gtest_discover_tests(dbapi_test)