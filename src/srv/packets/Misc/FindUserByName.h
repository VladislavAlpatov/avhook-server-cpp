//
// Created by vlad on 25.05.23.
//

#pragma once
#include "../BasePacket.h"


namespace web::packet::misc
{
    class FindUserByName : public BasePacket
    {
    public:
        explicit FindUserByName(const nlohmann::json &data);

        nlohmann::json ExecutePayload(ClientHandle &clientHandle) override;

    private:
        std::string m_sSearchName;
    };

}
