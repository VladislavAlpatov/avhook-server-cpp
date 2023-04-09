//
// Created by alpat on 06.04.2023.
//

#include "RSA.h"

#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/integer/mod_inverse.hpp>
#include <boost/random.hpp>


#include <iostream>
#include <array>
#include <thread>

using namespace boost::multiprecision;
using namespace boost::random;





namespace Encryption
{
	std::vector<uint8_t> RSA::Encrypt(const std::vector<uint8_t>& data) const
	{
		const auto szStep = m_szKeySize / 8;
		const auto szDataSize = data.size();

		std::vector<uint8_t> encryptedData;
		encryptedData.reserve((data.size() / szStep + 1) * (szStep*2+1) );

		for (size_t i = 0; i < szDataSize; i+= szStep)
		{
			cpp_int number;
			const auto szSizeOfData = (szDataSize - i >= szStep) ? szStep : szDataSize - i;

			import_bits(number, data.data()+i, data.data() + i + szSizeOfData);

			cpp_int encryptedNumber = powm<cpp_int>(number, m_NumberEncrypt, m_NumberN);

			std::vector<uint8_t> encBytes;
			export_bits(encryptedNumber, std::back_inserter(encBytes), 8);

			encryptedData.push_back(szSizeOfData);

			for (auto byte : encBytes)
				encryptedData.push_back(byte);

			for (int i = 0; i < szStep*2 - encBytes.size(); i++)
				encryptedData.push_back(NULL);
		}
		return encryptedData;

	}
	void RSA::GenerateKeys()
	{
		auto p = GeneratePrimeNumber();
		auto q = GeneratePrimeNumber();

		auto n = p*q;

		auto phi = (p - 1) * (q - 1);
		cpp_int e;

		mt19937 mt(time(nullptr));
		uniform_int_distribution<cpp_int> ui(2, phi-1);

		do
		{
			e = ui(mt);
		}
		while (gcd(e, phi) != 1);
		auto d = boost::integer::mod_inverse<cpp_int>(e, phi);

		m_NumberN       = n;
		m_NumberDecrypt = d;
		m_NumberEncrypt = e;
		// printf("n = %s\nd = %s\ne = %s\n", m_NumberN.str().c_str(), m_NumberDecrypt.str().c_str(), m_NumberEncrypt.str().c_str());
	}

	std::vector<uint8_t> RSA::Decrypt(const std::vector<uint8_t>& encData) const
	{
		const auto szEncryptedChunkSize = CalcChunkSize();

		// Check if encrypted data is corrupted
		if (encData.size() % szEncryptedChunkSize)
			throw std::runtime_error("ENCRYPTED DATA CORRUPTED");


		std::vector<uint8_t> decryptedData;
		decryptedData.reserve(CalcDecryptedDataSize(encData));

		for (size_t i = 0; i < encData.size(); i += szEncryptedChunkSize)
		{
			cpp_int encNumber;
			import_bits(encNumber, encData.data()+i+1, encData.data()+i+szEncryptedChunkSize);

			cpp_int decryptedNumber = powm<cpp_int>(encNumber, m_NumberDecrypt, m_NumberN);
			std::vector<uint8_t> decryptedBytes;
			export_bits(decryptedNumber, std::back_inserter(decryptedBytes), 8);

			for (const auto& byte : decryptedBytes)
				decryptedData.push_back(byte);


			int iMissingBytes = (uint8_t)encData[i] - decryptedData.size();

			for (int i = 0; i < iMissingBytes; i++)
				decryptedData.push_back(0);
		}
		return decryptedData;
	}

	cpp_int RSA::GeneratePrimeNumber() const
	{
		bool bFound = false;
		cpp_int foundNumber;
		mt19937 mt(std::time(nullptr));

		auto threadFunc = [&](bool* pFound, cpp_int* pNumber, int id)
		{
			uniform_int_distribution<cpp_int> ui(0, cpp_int(1) << (m_szKeySize-1) );
			while (!*pFound)
			{
				auto val =  ui(mt) | (cpp_int(1) << (m_szKeySize-1) ) | 1 ;

				if (miller_rabin_test(val,25))
				{
					*pFound = true;
					*pNumber = val;
					return;
				}
			}
		};
		std::vector<std::thread> threads;
		threads.reserve(4);

		for (int i = 0; i < 4; i++)
			threads.emplace_back(threadFunc,&bFound,&foundNumber, i);

		for (auto& thread : threads)
			thread.join();

		return foundNumber;
	}

	RSA::RSA(size_t szKeySize)
	{
		m_szKeySize = szKeySize;
		GenerateKeys();
	}

	size_t RSA::CalcDecryptedDataSize(const std::vector<uint8_t>& data) const
	{
		size_t size = 0;
		const auto szChunkSize = data.size();

		for (size_t i = 0; i < data.size(); i += szChunkSize)
			size += data[i];

		return size;
	}

	size_t RSA::CalcEncryptedDataSize(size_t szSize)
	{
		return szSize / m_szKeySize / 8 ;
	}

	[[maybe_unused]] RSA::RSA(const nlohmann::json& data)
	{
		try
		{
			m_NumberN       = cpp_int(data.at("n").get<std::string>());
			m_NumberEncrypt = cpp_int(data.at("e").get<std::string>());
			m_NumberDecrypt = cpp_int(data.at("d").get<std::string>());
			m_szKeySize     = msb(m_NumberN) / 2;
		}
		catch (...)
		{
			throw RSAInitializeError();
		}
	}

	const char* RSAInitializeError::what() const noexcept
	{
		return "Failed to create RSA class";
	}
}
