#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "../packets/Base.h"


namespace Web::Network
{
    std::string RecvString(int soc);
    nlohmann::json RecvJson(int soc);
    void SendString(int soc, const std::string& str);
    void SendJson(int soc, const nlohmann::json& jsn);
	std::shared_ptr<Web::Packet::Base> RecvPacket(int soc);
}

