//
// Created by alpat on 12.02.2023.
//

#pragma once

namespace DBAPI
{
    class Object
    {
    public:
        int GetID() const {return  m_iID;}
    protected:
        int m_iID;
    };
}