add_subdirectory(srv)
add_subdirectory(lib/sha256)
add_subdirectory(lib/sqlite)
add_subdirectory(lib/base64)
add_subdirectory(lib/crypto)

target_sources(server PRIVATE main.cpp)
