add_subdirectory(packets)
add_subdirectory(network)
add_subdirectory(ClientHandle)
add_subdirectory(observers)
add_subdirectory(DataBaseAPI)
add_subdirectory(factories)

target_sources(server PRIVATE server.cpp)