//
// Created by nullifiedvlad on 27.12.2022.
//
#pragma once
#include "../observers/ObservableObject.h"
#include "../packets/BasePacket.h"
#include "../network/Socket.h"
#include "../DataBaseAPI/User.h"
#include <cstdint>

#include <memory>

namespace web
{
	class ClientHandle final : public ObservableObject
	{
	public:
		ClientHandle(network::Socket soc);

		void Listen();
		~ClientHandle() override;
        network::Socket m_clientSocket;
		dbapi::User m_dbUser;
		void OnPacket(const std::unique_ptr<IPayloadExecutable>& pPacket);
	private:
		std::vector<uint8_t> m_xorKey;
		void SendBytes(const std::vector<uint8_t>& bytes);
		void SendString(const std::string& str);
		void SendJson(const nlohmann::json& jsn);

		[[nodiscard]] bool ExchangeRsaKeys();
		[[nodiscard]] std::string RecvString();
		[[nodiscard]] nlohmann::json RecvJson();
		[[nodiscard]] std::vector<uint8_t> RecvBytes();
		[[nodiscard]] std::unique_ptr<IPayloadExecutable> RecvPacket();
	};
}