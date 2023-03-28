//
// Created by alpat on 12.02.2023.
//

#pragma once
#include <cstdint>

#define INVALID_DATABASE_OBJECT_ID 0

namespace DBAPI
{
    class Object
    {
    public:
        Object() = default;
        Object(uint64_t id) {m_iID = id;}
        [[nodiscard]] uint64_t GetID() const {return  m_iID;}
    protected:
        uint64_t m_iID = 0;
    };
}