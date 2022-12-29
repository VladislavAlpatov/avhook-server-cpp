//
// Created by nullifiedvlad on 27.12.2022.
//
#pragma once
#include "../ObservableObject.h"
#include <memory>
#include "../packets/Base.h"

namespace Web
{
	class ClientHandle final : public ObservableObject
	{
	public:
		ClientHandle(int soc);

		void Listen();
		void AuthClient();
		~ClientHandle();
        int m_clientSocket;
		int m_iUserIdInDataBase = -1;
		void OnPacket(const std::shared_ptr<Web::Packet::Base>& pPacket) const;
	};
	void CreateNewThreadHandle(int clientSocket);
}