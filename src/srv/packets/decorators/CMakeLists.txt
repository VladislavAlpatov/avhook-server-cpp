target_sources(server PRIVATE
        BaseDecorator.cpp
        RegisteredOnly.cpp
        exceptions.h
        OwnerOnly.cpp
        AdminOnly.cpp
        ChatMembersOnly.cpp)