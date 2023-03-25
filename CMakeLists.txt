cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER   clang)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}${CMAKE_CURRENT_SOURCE_DIR}/cmake-scripts)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../out/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../out/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../out/${CMAKE_BUILD_TYPE}")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(_DEBUG)
else()
    add_link_options(-s)

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

find_package(OpenSSL REQUIRED)
target_link_libraries(server PRIVATE OpenSSL::Crypto)

add_subdirectory(tests)
