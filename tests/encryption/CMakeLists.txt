project(encryption)
add_executable(encryption main.cpp)



find_package(GTest REQUIRED)
target_link_libraries(encryption PRIVATE GTest::GTest GTest::Main)
gtest_discover_tests(encryption)