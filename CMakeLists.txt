cmake_minimum_required(VERSION 3.20)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER   clang)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../out/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../out/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../out/${CMAKE_BUILD_TYPE}")

option(BUILD_SERVER_TEST "Build GTests for server" ON)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(_DEBUG)
else()
    add_link_options(-s)
    add_compile_options(-Ofast)

endif()


project(server)
add_executable(server src/main.cpp)

add_subdirectory(src)

find_package(Boost REQUIRED)
target_link_libraries(server PRIVATE ${Boost_LIBRARIES})

find_package(SQLite3 REQUIRED)
target_link_libraries(server PRIVATE SQLite::SQLite3)

add_subdirectory(src/lib/json)
target_link_libraries( server PRIVATE nlohmann_json )

find_package(fmt REQUIRED)
target_link_libraries(server PRIVATE fmt::fmt)


if(BUILD_SERVER_TEST)
    add_subdirectory(tests)
endif()