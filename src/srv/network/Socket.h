//
// Created by Vlad on 06.01.2023.
//
#pragma once
#include "../packets/BasePacket.h"



typedef int SOCKET;



namespace web::Network
{

    class Socket
    {
    public:
        Socket(::SOCKET socket);
        Socket();

        [[maybe_unused]] SOCKET GetRawSocket() const;

        Socket(int af, int type, int protocol);
        virtual std::vector<uint8_t> RecvBytes() const;
        virtual void SendBytes(const void* pBytes, int iSize) const;
		void SendBytes(const std::vector<uint8_t>& bytes) const { SendBytes(bytes.data(), (int)bytes.size()); };
        void Bind(const std::string& ip, int iPort);
        void SetOption(int iProto,int iOption, int iOptionVal);
        void Close();
        Socket Listen();

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