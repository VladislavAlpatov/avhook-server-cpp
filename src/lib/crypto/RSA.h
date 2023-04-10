//
// Created by alpat on 06.04.2023.
//

#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <nlohmann/json.hpp>

namespace Encryption
{
	class RSA
	{
	public:
		explicit RSA(size_t szKeySize);
		RSA() = default;

		[[nodiscard]] std::vector<uint8_t> Encrypt(const std::vector<uint8_t>& data)    const;
		[[nodiscard]] std::vector<uint8_t> Decrypt(const std::vector<uint8_t>& encData) const;

		explicit RSA(const nlohmann::json& data);

		void GenerateKeys();

		[[nodiscard]] boost::multiprecision::cpp_int GetModulus()    const {return m_NumberN;}
		[[nodiscard]] boost::multiprecision::cpp_int GetPrivateKey() const {return m_NumberDecrypt;}
		[[nodiscard]] boost::multiprecision::cpp_int GetPublicKey()  const {return m_NumberEncrypt;}

	private:
		[[nodiscard]] boost::multiprecision::cpp_int GeneratePrimeNumber() const;
		size_t m_szKeySize = 0;
		size_t CalcEncryptedDataSize(size_t szSize);
		size_t CalcDecryptedDataSize(const std::vector<uint8_t>& data) const;

		[[nodiscard]] size_t CalcChunkSize() const {return m_szKeySize / 4 + 1;}

		boost::multiprecision::cpp_int m_NumberN;
		boost::multiprecision::cpp_int m_NumberDecrypt;
		boost::multiprecision::cpp_int m_NumberEncrypt;

		bool EncryptionDecryptionCheck() const;
	};

	class RSAInitializeError : public std::exception
	{
	public:
		const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
	};
} // Encryption
