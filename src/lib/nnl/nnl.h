#pragma once
#include <string>
#include <WinSock2.h>
#include <nlohmann/json.hpp>



namespace nnl
{
    std::string recv_string(SOCKET soc);
    nlohmann::json recv_json(SOCKET soc);
    void send_string(SOCKET soc, const std::string& str);
    
}

