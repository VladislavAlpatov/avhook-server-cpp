#include "network.h"
#include <memory>
#include "exceptions.h"
#include "../PacketFactory.h"
#include "../packets/exceptions.h"

std::string Web::Network::RecvString(SOCKET soc)
{
    int iSize = 0;
    ::recv(soc, (char*)&iSize, 4, NULL);

    if (iSize <= 0)
		throw Exception::RecvFailed();
    
    auto pBuff = std::unique_ptr<char>(new char[iSize+1]);
    

    pBuff.get()[iSize] = '\0';
	int iRecvdBytes = 0;
    while (iRecvdBytes < iSize)
    {
       const auto tmp = ::recv(soc, pBuff.get()+iRecvdBytes, iSize-iRecvdBytes, NULL);
       
       if (!tmp) throw Exception::RecvFailed();
	   iRecvdBytes += tmp;
    }

    return pBuff.get();   
}

nlohmann::json Web::Network::RecvJson(SOCKET soc)
{
    return nlohmann::json::parse(RecvString(soc));
}

void Web::Network::SendString(SOCKET soc, const std::string& str)
{
    ::send(soc, str.c_str(), str.size(), NULL);
}

void Web::Network::SendJson(SOCKET soc, const nlohmann::json& jsn)
{
	SendString(soc, jsn.dump());
}

std::shared_ptr<Web::Packet::Base> Web::Network::RecvPacket(SOCKET soc)
{
	try
	{
		return Web::PacketFactory::Create(RecvJson(soc));
	}
	catch (const nlohmann::json::exception& ex)
	{
		throw Web::Packet::Exception::CorruptedPacket();
	}
}
