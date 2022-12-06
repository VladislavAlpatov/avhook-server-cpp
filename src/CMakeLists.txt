add_subdirectory(srv)
add_subdirectory(lib/sha256)
add_subdirectory(lib/sqlite)

target_sources(server PRIVATE main.cpp)
