target_sources(server PRIVATE
        BaseDecorator.cpp
        RegisteredOnly.cpp
        exceptions.h
        CantModifyOtherUsers.cpp
        AdminOnly.cpp)