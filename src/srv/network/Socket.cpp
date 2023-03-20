#include "Socket.h"
#include "exceptions.h"

#include "../factories/PacketFactory.h"
#include "../packets/exceptions.h"

#if defined(_WIN32)
#include <winsock2.h>
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

    [[maybe_unused]] SOCKET Socket::GetRawSocket() const
    {
        return m_pRawSocket;
    }

    std::string Socket::RecvString() const
    {
        return (char*)RecvBytes().get();
    }

    nlohmann::json Socket::RecvJson() const
    {
        return nlohmann::json::parse(RecvString());
    }

    void Socket::SendString(const std::string &str) const
    {
        SendBytes(str.c_str(), str.size());
    }

    void Socket::SendJson(const nlohmann::json &jsn) const
    {
        SendString(jsn.dump());
    }

    std::unique_ptr<Web::Packet::BasePacket> Socket::RecvPacket() const
    {
        return Web::PacketFactory::Create(RecvJson());
    }

    Socket::Socket(int af, int type, int protocol)
    {
        m_pRawSocket = socket(af, type, protocol);
    }

    void Socket::Bind(const std::string &ip, int iPort)
    {
#if defined(_WIN32) // Windows
        SOCKADDR_IN addr;
        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.S_un.S_addr);
        addr.sin_port = htons(iPort);
        addr.sin_family = AF_INET;

        bind(*m_pRawSocket, (SOCKADDR *) &addr, sizeof(addr));
#else // Linux
        sockaddr_in addr{};

        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.s_addr);
        addr.sin_port = htons(iPort);
        addr.sin_family = AF_INET;

        bind(m_pRawSocket, (sockaddr*)&addr, sizeof(addr));
#endif
    }

    Socket Socket::Listen()
    {
        listen(m_pRawSocket, SOMAXCONN);

        auto connectionSocket = accept(m_pRawSocket, NULL, NULL);

        if (!connectionSocket) throw Exception::SocketAcceptionFaild();

        return connectionSocket;
    }

    Socket::Socket(::SOCKET socket)
    {
        m_pRawSocket = socket;
    }

    Socket::Socket()
    {
        m_pRawSocket = -1;
    }

    std::unique_ptr<uint8_t> Socket::RecvBytes() const
    {
        int iSize = 0;
        ::recv(m_pRawSocket, (char*)&iSize, 4, NULL);

        if (iSize <= 0 || iSize > MAX_ACCEPTABLE_PACKET_SIZE)
            throw Exception::RecvFailed();

        auto pBuff = std::unique_ptr<uint8_t>(new uint8_t[iSize+1]);

        pBuff.get()[iSize] = '\0';
        int iRecvdBytes = 0;
        while (iRecvdBytes < iSize)
        {
            const auto tmp = ::recv(m_pRawSocket, (char*)pBuff.get()+iRecvdBytes, iSize-iRecvdBytes, NULL);

            if (!tmp) throw Exception::RecvFailed();
            iRecvdBytes += tmp;
        }

        return pBuff;
    }

    void Socket::SendBytes(const void *pBytes, int iSize) const
    {
        ::send(m_pRawSocket, (const char*)&iSize, sizeof(iSize), MSG_NOSIGNAL);
        ::send(m_pRawSocket, (const char*)pBytes, iSize, MSG_NOSIGNAL);
    }

    void Socket::Close()
    {
        close(m_pRawSocket);
        m_pRawSocket = -1;
    }

    void Socket::SetOption(int iProto, int iOption, int iOptionVal)
    {
        const auto res = setsockopt(m_pRawSocket, iProto, iOption, &iOptionVal, sizeof(iOptionVal));

        if (res == -1)
            throw std::runtime_error("Failed to set opt to socket");
    }

}