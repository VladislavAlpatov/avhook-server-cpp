cmake_minimum_required(VERSION 3.23)
set(CMAKE_CXX_STANDARD 23)
add_compile_definitions(WIN32_LEAN_AND_MEAN )
add_link_options(-pthread)

project(server)
add_executable(server src/main.cpp)

add_subdirectory(src)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(server PRIVATE unofficial::sqlite3::sqlite3)

target_link_libraries(server PRIVATE ws2_32)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(server PRIVATE nlohmann_json::nlohmann_json)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(server PRIVATE fmt::fmt-header-only)

find_package(ZLIB REQUIRED)
target_link_libraries(server PRIVATE ZLIB::ZLIB)