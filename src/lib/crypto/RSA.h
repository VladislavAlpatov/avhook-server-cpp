//
// Created by alpat on 06.04.2023.
//

#pragma once

#include <boost/multiprecision/cpp_int.hpp>


namespace Encryption
{
	class RSA
	{
	public:
		explicit RSA(size_t szKeySize);
		[[nodiscard]] std::vector<uint8_t> Encrypt(const std::vector<uint8_t>& data)    const;
		[[nodiscard]] std::vector<uint8_t> Decrypt(const std::vector<uint8_t>& encData) const;

		void GenerateKeys();
	private:
		[[nodiscard]] boost::multiprecision::cpp_int GeneratePrimeNumber() const;
		size_t m_szKeySize;
		size_t CalcEncryptedDataSize(size_t szSize);
		[[nodiscard]] size_t CalcChunkSize() const {return m_szKeySize / 8 + 1;}
		boost::multiprecision::cpp_int m_NumberN;
		boost::multiprecision::cpp_int m_NumberDecrypt;
		boost::multiprecision::cpp_int m_NumberEncrypt;
	};


} // Encryption
