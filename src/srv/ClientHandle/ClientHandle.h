//
// Created by nullifiedvlad on 27.12.2022.
//
#pragma once
#include "../ObservableObject.h"
#include <memory>
#include "../packets/BasePacket.h"
#include "../network/Socket.h"

#define INVALID_USER_ID (-1)

namespace Web
{
	class ClientHandle final : public ObservableObject
	{
	public:
		explicit ClientHandle(const Network::Socket& soc);

		void Listen();
		~ClientHandle() override;
        Network::Socket m_clientSocket;
		int m_iUserId = -1;
		void OnPacket(const std::unique_ptr<Web::Packet::BasePacket>& pPacket);
	};
}