//
// Created by nullifiedvlad on 27.12.2022.
//
#pragma once
#include "../ObservableObject.h"
#include <memory>
#include "../packets/BasePacket.h"
#include "../network/Socket.h"

namespace Web
{
	class ClientHandle final : public ObservableObject
	{
	public:
		explicit ClientHandle(const Network::Socket& soc);

		void Listen();
		void AuthClient();
		~ClientHandle() override;
        Network::Socket m_clientSocket;
		int m_iUserIdInDataBase = -1;
		void OnPacket(const std::shared_ptr<Web::Packet::BasePacket>& pPacket) const;
	};
}