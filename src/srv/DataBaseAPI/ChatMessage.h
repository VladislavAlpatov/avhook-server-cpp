//
// Created by Vladislav on 3/19/2023.
//

#pragma once
#include "Object.h"

#include <string>

namespace DBAPI
{
    class User;
    class Chat;

    class ChatMessage final : public Object
    {
        friend class DataBase;
        friend class Chat;
    public:
        ChatMessage() = default;
        [[nodiscard]] User GetOwner()       const;
        [[nodiscard]] Chat GetChat()        const;
        [[nodiscard]] std::string GetText() const;
        void SetText(std::string text);
    private:
        ChatMessage(uint64_t id);
    };

}