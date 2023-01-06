cmake_minimum_required(VERSION 3.23)

if (NOT WIN32)

    set(CMAKE_CXX_COMPILER clang++)
    set(CMAKE_C_COMPILER clang)

    set(CMAKE_TOOLCHAIN_FILE /root/vcpkg/scripts/buildsystems/vcpkg.cmake)
    set(VCPKG_TARGET_TRIPLET x64-linux)

    add_link_options(-pthread -static)
else()
    set(CMAKE_CXX_COMPILER cl.exe)
    set(CMAKE_C_COMPILER cl.exe)

    set(CMAKE_TOOLCHAIN_FILE C:/Users/Vlad/Documents/vcpkg/scripts/buildsystems/vcpkg.cmake)
    set(VCPKG_TARGET_TRIPLET x64-windows-static)
endif()

set(CMAKE_CXX_STANDARD 23)

add_compile_definitions(WIN32_LEAN_AND_MEAN )



project(server)
add_executable(server src/main.cpp src/srv/packets/SendChatMessage.cpp src/srv/packets/SendChatMessage.h)

add_subdirectory(src)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
target_link_libraries(server PRIVATE unofficial::sqlite3::sqlite3)

if (WIN32)
    target_link_libraries(server PRIVATE ws2_32)
endif()

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(server PRIVATE nlohmann_json::nlohmann_json)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(server PRIVATE fmt::fmt-header-only)

find_package(ZLIB REQUIRED)
target_link_libraries(server PRIVATE ZLIB::ZLIB)