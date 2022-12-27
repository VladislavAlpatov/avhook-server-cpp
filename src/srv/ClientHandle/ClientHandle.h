//
// Created by nullifiedvlad on 27.12.2022.
//
#pragma once
#include <WinSock2.h>
#include "../ObservableObject.h"
#include <memory>
#include "../packets/Base.h"

namespace Web
{
	class ClientHandle final : public ObservableObject
	{
	public:
		ClientHandle(SOCKET soc);

		void Listen();
		void AuthClient();
		~ClientHandle();
	private:
		SOCKET m_clientSocket;
		int m_iUserIdInDataBase = -1;
		void OnPacket(const std::shared_ptr<Web::Packet::Base>& pPacket) const;
	};
	void CreateNewThreadHandle(SOCKET clientSocket);
}