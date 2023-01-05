#pragma once
#include <string>
#include <winsock2.h>
#include <nlohmann/json.hpp>
#include "../packets/Base.h"


namespace Web::Network
{
    std::string RecvString(SOCKET soc);
    nlohmann::json RecvJson(SOCKET soc);

    void SendString(SOCKET soc, const std::string& str);
    void SendJson(SOCKET soc, const nlohmann::json& jsn);
	std::shared_ptr<Web::Packet::Base> RecvPacket(SOCKET soc);
}

