//
// Created by vladislav on 08.03.23.
//

#pragma once
#include "../BasePacket.h"


namespace Web::Packet::User
{
    class SetName final : public BasePacket
    {
    public:
        explicit SetName(const nlohmann::json &data);

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;

    private:
        int m_iUserID;
        std::string m_sNewUserName;
    };
}
