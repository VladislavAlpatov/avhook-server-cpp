#include "nnl.h"
#include <memory>
#include "exceptions.h"

std::string nnl::recv_string(SOCKET soc)
{
    int iSize = 0;
    ::recv(soc, (char*)&iSize, 4, NULL);

    if (iSize <= 0)
		throw exception::RecvFailed();
    
    auto pBuff = std::unique_ptr<char>(new char[iSize+1]);
    

    pBuff.get()[iSize] = '\0';
	int iRecvdBytes = 0;
    while (iRecvdBytes < iSize)
    {
       const auto tmp = ::recv(soc, pBuff.get()+iRecvdBytes, iSize-iRecvdBytes, NULL);
       
       if (!tmp) throw exception::RecvFailed();
	   iRecvdBytes += tmp;
    }

    return pBuff.get();   
}

nlohmann::json nnl::recv_json(SOCKET soc)
{
    return nlohmann::json::parse(recv_string(soc));
}

void nnl::send_string(SOCKET soc, const std::string& str)
{
    ::send(soc, str.c_str(), str.size(), NULL);
}