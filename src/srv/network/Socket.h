//
// Created by Vlad on 06.01.2023.
//
#pragma once
#include "../packets/BasePacket.h"



typedef int SOCKET;



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
        [[nodiscard]] std::string RecvString() const;
        [[nodiscard]] nlohmann::json RecvJson() const;
        void SendString(const std::string& str) const;
        void SendJson(const nlohmann::json& jsn) const;
        void Bind(const std::string& ip, int iPort);
        void SetOption(int iProto,int iOption, int iOptionVal);
        void Close();
        Socket Listen();
        [[nodiscard]] std::unique_ptr<IPayloadExecutable> RecvPacket() const;

        template<typename Type>
        void SendStruct(const Type& strct) const
        {
            SendBytes((void*)&strct, sizeof(Type));
        }

    private:
        // Use std::shared_ptr to close socket automatically after it become useless
        SOCKET m_pRawSocket;
    };

} // Network