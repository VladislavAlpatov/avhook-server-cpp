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


inline size_t GetCppIntSize(const cpp_int& number)
{
	return ceil(( (float)msb(number) + 1) / 8.f);
}


namespace Encryption
{
	std::vector<uint8_t> RSA::Encrypt(const std::vector<uint8_t>& data) const
	{
		const auto szStep = GetKeySize();
		const auto szDataSize = data.size();

		std::vector<uint8_t> encryptedData;

		for (size_t i = 0; i < szDataSize; i += szStep)
		{
			cpp_int number;
			const auto szSizeOfData = (szDataSize - i >= szStep) ? szStep : szDataSize - i;

			import_bits(number, data.data()+i, data.data() + i + szSizeOfData);
			cpp_int encryptedNumber = powm<cpp_int>(number, m_NumberEncrypt, m_NumberN);

			size_t encNumberSize = GetCppIntSize(encryptedNumber);

			size_t missingBytes = GetModulusSize() - encNumberSize;

			encryptedData.push_back(szSizeOfData);

			for (size_t j = 0; j < missingBytes; j++)
				encryptedData.push_back(0);

			export_bits(encryptedNumber, std::back_inserter(encryptedData), 8);

		}
		return encryptedData;

	}

	std::vector<uint8_t> RSA::Decrypt(const std::vector<uint8_t>& encData) const
	{
		const auto szEncryptedChunkSize = GetModulusSize() + 1;

		// Check if encrypted data is corrupted
		if (encData.size() % szEncryptedChunkSize)
			throw std::runtime_error("ENCRYPTED DATA CORRUPTED");


		std::vector<uint8_t> decryptedData;

		for (size_t i = 0; i < encData.size(); i += szEncryptedChunkSize)
		{
			cpp_int encNumber;
			import_bits(encNumber, encData.data()+i+1, encData.data()+i+szEncryptedChunkSize);
			cpp_int decryptedNumber = powm<cpp_int>(encNumber, m_NumberDecrypt, m_NumberN);
			export_bits(decryptedNumber, std::back_inserter(decryptedData), 8);

			size_t decNumberSize = GetCppIntSize(decryptedNumber);
			int szMissingBytes   = *(encData.data()+i) - decNumberSize;

			for (size_t i = 0; i < szMissingBytes; i++)
				decryptedData.push_back(0);

		}
		return decryptedData;
	}

	cpp_int RSA::GeneratePrimeNumber(size_t szBits) const
	{
		static mt19937 gen(time(0));
		static uniform_int_distribution<cpp_int> dist(cpp_int(1) << (szBits - 1), (cpp_int(1) << szBits) - 1);
		cpp_int p;
		do
		{
			p = dist(gen);
		}
		while (!miller_rabin_test(p, 50));
		return p;
	}

	RSA::RSA(size_t szKeySize)
	{
		auto p = GeneratePrimeNumber(szKeySize);
		auto q = GeneratePrimeNumber(szKeySize);

		auto n = p*q;

		auto phi = (p - 1) * (q - 1);

		static mt19937 mt(time(nullptr));
		uniform_int_distribution<cpp_int> ui(2, phi-1);

		cpp_int e = 65537;
		while (gcd(e, phi) != 1)
		{
			e = ui(mt);
		}
		auto d = boost::integer::mod_inverse<cpp_int>(e, phi);

		m_NumberN       = n;
		m_NumberDecrypt = d;
		m_NumberEncrypt = e;
	}


	[[maybe_unused]] RSA::RSA(const nlohmann::json& data)
	{
		try
		{
			m_NumberN       = cpp_int(data.at("n").get<std::string>());
			m_NumberEncrypt = cpp_int(data.at("e").get<std::string>());
			m_NumberDecrypt = cpp_int(data.at("d").get<std::string>());

		}
		catch (...)
		{
			throw RSAInitializeError();
		}
	}

	size_t RSA::GetModulusSize() const
	{
		return GetCppIntSize(m_NumberN);
	}

	const char* RSAInitializeError::what() const noexcept
	{
		return "Failed to create RSA class";
	}
}
