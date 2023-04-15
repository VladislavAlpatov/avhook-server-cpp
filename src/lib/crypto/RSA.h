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
		RSA() = default;

		void SetPrivateKey(const boost::multiprecision::cpp_int& newPrivateKeyNumber);
		void SetPublicKey(const boost::multiprecision::cpp_int& newPublicNumber);
		void SetModulus(const boost::multiprecision::cpp_int& newModulusNumber);

		[[nodiscard]] std::vector<uint8_t> Encrypt(const std::vector<uint8_t>& data)    const;
		[[nodiscard]] std::vector<uint8_t> Decrypt(const std::vector<uint8_t>& encData) const;
		[[nodiscard]] inline boost::multiprecision::cpp_int GetModulus()    const {return m_NumberN;}
		[[nodiscard]] inline boost::multiprecision::cpp_int GetPrivateKey() const {return m_NumberDecrypt;}
		[[nodiscard]] inline boost::multiprecision::cpp_int GetPublicKey()  const {return m_NumberEncrypt;}

	private:
		[[nodiscard]] boost::multiprecision::cpp_int GeneratePrimeNumber(size_t szBits) const;
		[[nodiscard]] size_t GetModulusSize()    const;
		[[nodiscard]] inline size_t GetKeySize() const {return GetModulusSize() / 2;};
		[[nodiscard]] bool ValidateDataPadding(const std::vector<uint8_t>& encData) const;

		boost::multiprecision::cpp_int m_NumberN       = 0;
		boost::multiprecision::cpp_int m_NumberDecrypt = 0;
		boost::multiprecision::cpp_int m_NumberEncrypt = 0;
	};

	class RSAInitializeError : public std::exception
	{
	public:
		[[nodiscard]] const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
	};
	class RSADecryptionError : public std::exception
	{
	public:
		[[nodiscard]] const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
	};
	class RSAInvalidPrivateKey : public std::exception
	{
	public:
		[[nodiscard]] const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
	};
	class RSAInvalidPublicKey : public std::exception
	{
	public:
		[[nodiscard]] const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
	};
	class RSAInvalidModulus : public std::exception
	{
	public:
		[[nodiscard]] const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
	};
} // Encryption
