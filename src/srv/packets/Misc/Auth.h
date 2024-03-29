//
// Created by nullifiedvlad on 08.12.2022.
//
#pragma once
#include "../BasePacket.h"


namespace web::packet::Misc
{

    class Auth final : public BasePacket
    {
    public:
        explicit Auth(const nlohmann::json &data);
        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    private:
        std::string m_sUserPasswordHash;
        std::string m_sUserEmail;
    };

} // packet