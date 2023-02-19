//
// Created by Vlad on 06.01.2023.
//
#pragma once
#include "../packets/BasePacket.h"



#if defined(_WIN32)
typedef unsigned long long SOCKET;
#else
typedef int SOCKET;
#endif


namespace Web::Network
{

    class Socket
    {
    public:
        Socket(::SOCKET socket);
        Socket();

        [[maybe_unused]] SOCKET GetRawSocket() const;

        Socket(int af, int type, int protocol);
        virtual std::unique_ptr<uint8_t> RecvBytes() const;
        virtual void SendBytes(const void* pBytes, int iSize) const;
        std::string RecvString() const;
        nlohmann::json RecvJson() const;
        void SendString(const std::string& str) const;
        void SendJson(const nlohmann::json& jsn) const;
        void Bind(const std::string& ip, int iPort);
        Socket Listen();
        std::unique_ptr<Packet::BasePacket> RecvPacket() const;

        template<typename Type>
        void SendStruct(const Type& strct) const
        {
            SendBytes((void*)&strct, sizeof(Type));
        }

    private:
        std::shared_ptr<SOCKET> m_pRawSocket;
    };

} // Network