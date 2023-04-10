project(dbapi)
add_executable(dbapi main.cpp)


file(GLOB dbapi_SRC "../../src/srv/DataBaseAPI/*.cpp" "../../src/lib/sqlite/*.cpp" "../../src/lib/base64/*.cpp")


target_sources(dbapi PRIVATE ${dbapi_SRC})
target_include_directories(dbapi PRIVATE ../../src/srv/DataBaseAPI)

find_package(GTest REQUIRED)
target_link_libraries(dbapi PRIVATE GTest::GTest GTest::Main)
target_link_libraries(dbapi PRIVATE ${Boost_LIBRARIES})
target_link_libraries(dbapi PRIVATE SQLite::SQLite3)
target_link_libraries(dbapi PRIVATE nlohmann_json )
target_link_libraries(dbapi PRIVATE fmt::fmt)

gtest_discover_tests(dbapi)