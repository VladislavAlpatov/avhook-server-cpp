//
// Created by Vlad on 27.12.2022.
//
#include "ClientHandle.h"
#include "../observers/OnPacket.h"
#include "../network/exceptions.h"
#include "../factories/PacketFactory.h"
#include "../../lib/crypto/Xor.h"
#include "../../lib/crypto/RSA.h"


void Web::ClientHandle::Listen()
{
	if (!ExchangeRsaKeys())
		return;

    while (true)
    {
        try
        {
            OnPacket(RecvPacket());
        }
        catch (const Network::Exception::RecvFailed& ex)
        {
            return;
        }
        catch (const std::exception& ex)
        {
            nlohmann::json jsn;

            jsn["success"]    = false;
            jsn["error_code"] = ex.what();

            SendJson(jsn);
        }
    }
}

Web::ClientHandle::~ClientHandle()
{
    m_clientSocket.Close();
}

void Web::ClientHandle::OnPacket(const std::unique_ptr<IPayloadExecutable>& pPacket)
{
	NotifyObserver<Observers::OnPacket>();
	auto jsn = pPacket->ExecutePayload(*this);
	jsn["success"] = true;

    SendJson(jsn);
}

Web::ClientHandle::ClientHandle(Network::Socket soc)
{
	m_clientSocket = soc;
}

void Web::ClientHandle::SendString(const std::string& str)
{
	std::vector<uint8_t> data(str.begin(), str.end());
	SendBytes(data);
}

void Web::ClientHandle::SendJson(const nlohmann::json& jsn)
{
	SendString(jsn.dump());
}

std::string Web::ClientHandle::RecvString()
{
	auto data = RecvBytes();
	return { data.begin(), data.end()} ;
}

nlohmann::json Web::ClientHandle::RecvJson()
{
	return nlohmann::json::parse(RecvString());
}

std::unique_ptr<Web::IPayloadExecutable> Web::ClientHandle::RecvPacket()
{
	return PacketFactory::Create(RecvJson());
}

bool Web::ClientHandle::ExchangeRsaKeys()
{
	try
	{
		static const auto rsa = Encryption::RSA(1024);

		nlohmann::json rsaInJsn;
		rsaInJsn["n"] = rsa.GetModulus().str();
		rsaInJsn["e"] = rsa.GetPublicKey().str();

		const auto jsnStr = rsaInJsn.dump();
		m_clientSocket.SendBytes(jsnStr.data(), jsnStr.size());
		m_xorKey = rsa.Decrypt(m_clientSocket.RecvBytes());

		return true;
	}
	catch (...)
	{
		return false;
	}


}

std::vector<uint8_t> Web::ClientHandle::RecvBytes()
{
	return Encryption::Xor::Decrypt(m_clientSocket.RecvBytes(), m_xorKey);
}

void Web::ClientHandle::SendBytes(const std::vector<uint8_t>& bytes)
{
	const auto encData = Encryption::Xor::Decrypt(bytes, m_xorKey);
	m_clientSocket.SendBytes(encData.data(), encData.size());
}

