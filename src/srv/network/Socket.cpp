#include "Socket.h"
#include "exceptions.h"

#include "../PacketFactory.h"
#include "../packets/exceptions.h"

#if defined(_WIN32) and __has_include("winsock2.h")

#include <ws2tcpip.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#define MAX_ACCEPTABLE_PACKET_SIZE 10485760

namespace Web::Network
{

    SOCKET Socket::GetRawSocket() const
    {
        return *m_pRawSocket;
    }

    std::string Socket::RecvString() const
    {
        int iSize = 0;
        ::recv(*m_pRawSocket, (char*)&iSize, 4, NULL);

        if (iSize <= 0 || iSize > MAX_ACCEPTABLE_PACKET_SIZE)
            throw Exception::RecvFailed();

        auto pBuff = std::unique_ptr<char>(new char[iSize+1]);


        pBuff.get()[iSize] = '\0';
        int iRecvdBytes = 0;
        while (iRecvdBytes < iSize)
        {
            const auto tmp = ::recv(*m_pRawSocket, pBuff.get()+iRecvdBytes, iSize-iRecvdBytes, NULL);

            if (!tmp) throw Exception::RecvFailed();
            iRecvdBytes += tmp;
        }

        return pBuff.get();
    }

    nlohmann::json Socket::RecvJson() const
    {
        return nlohmann::json::parse(RecvString());
    }

    void Socket::SendString(const std::string &str) const
    {
        int iSize = str.size();

        ::send(*m_pRawSocket, (const char*)&iSize, sizeof(iSize), NULL);
        ::send(*m_pRawSocket, str.c_str(), str.size(), NULL);
    }

    void Socket::SendJson(const nlohmann::json &jsn) const
    {
        SendString(jsn.dump());
    }

    std::shared_ptr<Web::Packet::BasePacket> Socket::RecvPacket() const
    {
        try
        {
            return Web::PacketFactory::Create(RecvJson());
        }
        catch (const nlohmann::json::exception& ex)
        {
            throw Web::Packet::Exception::CorruptedPacket();
        }
    }

    Socket::Socket(int af, int type, int protocol)
    {
        m_pRawSocket = std::shared_ptr<SOCKET>(new SOCKET);
        *m_pRawSocket = socket(af, type, protocol);
    }

    void Socket::Bind(const std::string &ip, int iPort)
    {
        SOCKADDR_IN addr;
        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.S_un.S_addr);
        addr.sin_port = htons(iPort);
        addr.sin_family = AF_INET;

        int status = bind(*m_pRawSocket, (SOCKADDR *) &addr, sizeof(addr));
    }

    Socket Socket::Listen()
    {
        listen(*m_pRawSocket, SOMAXCONN);
        sockaddr_in addr{};
        int size = sizeof(addr);

        auto connectionSocket = accept(*m_pRawSocket, (sockaddr *) &addr, &size);

        if (!connectionSocket) throw Exception::SocketAcceptionFaild();

        return connectionSocket;
    }

    Socket::Socket(SOCKET socket)
    {
        m_pRawSocket = std::shared_ptr<SOCKET>(new SOCKET);
        *m_pRawSocket = socket;
    }

    Socket::Socket()
    {
        // AF_INET, SOCK_STREAM, IPPROTO_TCP
        m_pRawSocket = std::shared_ptr<SOCKET>(new SOCKET);
        *m_pRawSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }
}