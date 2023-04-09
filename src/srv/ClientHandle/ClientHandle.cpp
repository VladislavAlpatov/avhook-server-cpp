//
// Created by Vlad on 27.12.2022.
//
#include "ClientHandle.h"
#include "../observers/OnPacket.h"
#include "../network/exceptions.h"
#include "../factories/PacketFactory.h"

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
	m_RsaIn = Encryption::RSA(1024);
}

void Web::ClientHandle::SendString(const std::string& str)
{
	std::vector<uint8_t> data(str.begin(), str.end());
	const auto encData = m_RsaOut.Encrypt(data);
	m_clientSocket.SendBytes(encData.data(), encData.size());
}

void Web::ClientHandle::SendJson(const nlohmann::json& jsn)
{
	SendString(jsn.dump());
}

std::string Web::ClientHandle::RecvString()
{
	auto data = m_RsaIn.Decrypt(m_clientSocket.RecvBytes());
	data.push_back('\0');
	return (char*)data.data();
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
		auto data = m_clientSocket.RecvBytes();
		data.push_back('\0');

		m_RsaOut = Encryption::RSA(nlohmann::json::parse(data.data()));

		nlohmann::json rsaInJsn;
		rsaInJsn["n"] = m_RsaIn.GetModulus().str();
		rsaInJsn["e"] = m_RsaIn.GetPublicKey().str();
		rsaInJsn["d"] = "0";

		const auto jsnStr = rsaInJsn.dump();
		m_clientSocket.SendBytes(jsnStr.data(), jsnStr.size());

		return true;
	}
	catch (...)
	{
		return false;
	}


}

