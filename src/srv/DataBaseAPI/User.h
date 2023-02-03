//
// Created by alpat on 03.02.2023.
//

#pragma once
#include <string>

namespace DBAPI
{
    class User
    {
        friend class DataBase;
    public:
        User() = default;
        int GetID() const {return m_iID;};
        std::string GetName()     const;
        std::string GetStatus()   const;
        int         GetType()     const;
        std::string GetPassword() const;
        std::string GetEmail()    const;

        void SetName(const std::string& sName);
        void SetStatus(const std::string& sStatus);
        void SetType(int iType);
        void SetEmail(const std::string& sEmail);
    private:
        int m_iID = 0;
        User(int iUserId);
    };

} // DBAPI
