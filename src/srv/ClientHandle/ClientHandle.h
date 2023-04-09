//
// Created by nullifiedvlad on 27.12.2022.
//
#pragma once
#include "../observers/ObservableObject.h"
#include "../packets/BasePacket.h"
#include "../network/Socket.h"
#include "../DataBaseAPI/User.h"
#include "../../lib/crypto/RSA.h"

#include <memory>

namespace Web
{
	class ClientHandle final : public ObservableObject
	{
	public:
		explicit ClientHandle(Network::Socket soc);

		void Listen();
		~ClientHandle() override;
        Network::Socket m_clientSocket;
		DBAPI::User m_dbUser;
		void OnPacket(const std::unique_ptr<IPayloadExecutable>& pPacket);
	private:
		Encryption::RSA m_RsaOut;
		Encryption::RSA m_RsaIn;
		void SendString(const std::string& str);
		void SendJson(const nlohmann::json& jsn);
		void ExchangeRsaKeys();
		[[nodiscard]] std::string RecvString();
		[[nodiscard]] nlohmann::json RecvJson();
		[[nodiscard]] std::unique_ptr<IPayloadExecutable> RecvPacket();
	};
}