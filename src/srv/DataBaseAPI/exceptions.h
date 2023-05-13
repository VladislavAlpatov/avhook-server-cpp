//
// Created by alpat on 04.02.2023.
//

#pragma once
#include <exception>



namespace DBAPI::Exception
{
    class UserNotFound final : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "User not found";
        }
    };
    class ChatNotFound final : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "Chat not found";
        }
    };
    class ChatMessageIsNotValid final : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "Message is wierd lol";
        }
    };
    class ChatMessageNotFound final : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "Message not found";
        }
    };
    class UserNotInChat final : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "User not in chat";
        }
    };
    class UserAlreadyInChat final : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "User already in chat, impossible to add twice";
        }
    };
	class UserNameIsInvalid final : public std::exception
	{
	public:
		const char* what() const noexcept override
		{
			return "User name is invalid, it should not contain spaces";
		}

	};
    class ConfigNotFound final : public std::exception
    {
    public:
        const char *what() const noexcept override
        {
            return "Failed to get config by id";
        }
    };
}

