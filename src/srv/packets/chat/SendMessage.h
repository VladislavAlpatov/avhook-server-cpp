//
// Created by Vladislav on 3/19/2023.
//

#pragma once
#include "ChatRelated.h"


namespace web::packet::chat
{
    class SendMessage final : public ChatRelated
    {
    public:
        explicit SendMessage(const nlohmann::json &data);

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;
    private:
        std::string m_sMessageText;
    };

}