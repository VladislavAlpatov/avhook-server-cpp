target_sources(server PRIVATE server.cpp PacketFactory.cpp)
add_subdirectory(packets)
add_subdirectory(network)
add_subdirectory(ClientHandle)