//
// Created by alpat on 03.02.2023.
//

#pragma once
#include <string>
#include "Object.h"

namespace DBAPI
{
    class User final : public Object
    {
        friend class DataBase;
    public:
        User() = default;
        std::string GetName()     const;
        std::string GetStatus()   const;
        int         GetType()     const;
        std::string GetPassword() const;
        std::string GetEmail()    const;

        void SetName(const std::string& sName);
        void SetStatus(const std::string& sStatus);
        void SetType(int iType);
        void SetEmail(const std::string& sEmail);
        bool IsUserNameAcceptable(const std::string& name) const;
    private:
        User(int iUserId);
    };

} // DBAPI
