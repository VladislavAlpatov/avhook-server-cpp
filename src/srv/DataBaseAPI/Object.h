//
// Created by alpat on 12.02.2023.
//

#pragma once

namespace DBAPI
{
    class Object
    {
    public:
        Object() = default;
        Object(int id) {m_iID = id;}
        int GetID() const {return  m_iID;}
    protected:
        int m_iID = -1;
    };
}