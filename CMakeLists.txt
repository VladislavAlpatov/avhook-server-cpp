cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

add_link_options(-pthread)



if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(_DEBUG)
else()
    add_link_options(-s)
endif()



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../out/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../out/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../out/${CMAKE_BUILD_TYPE}")
set(nlohmann_json "lib/json")

project(server)
add_executable(server src/main.cpp)

add_compile_definitions(WIN32_LEAN_AND_MEAN)

add_subdirectory(src)

find_package(Boost REQUIRED)
target_link_libraries(server PRIVATE ${Boost_LIBRARIES})

find_package(SQLite3)
target_link_libraries(server PRIVATE SQLite::SQLite3)

add_subdirectory(src/lib/json)
target_link_libraries( server PRIVATE nlohmann_json )

find_package(fmt CONFIG REQUIRED)
target_link_libraries(server PRIVATE fmt::fmt)

if (WIN32)
    target_link_libraries(server PRIVATE ws2_32)
endif()