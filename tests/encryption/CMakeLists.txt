project(encryption)
add_executable(encryption main.cpp)

file(GLOB encryption_SRC "../../src/lib/crypto/*.cpp")
target_sources(encryption PRIVATE ${encryption_SRC})
target_include_directories(encryption PRIVATE ../../src/lib/crypto)

find_package(GTest REQUIRED)
target_link_libraries(encryption PRIVATE GTest::GTest GTest::Main)
target_link_libraries(encryption PRIVATE ${Boost_LIBRARIES})
target_link_libraries(encryption PRIVATE nlohmann_json )

gtest_discover_tests(encryption)