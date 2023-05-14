//
// Created by alpat on 10.04.2023.
//
#include <gtest/gtest.h>
#include <RSA.h>
#include <Xor.h>

#include <iostream>

// Generate a random prime number using the Miller-Rabin primality test

TEST(RSA, ValidEncryptionAndDecryption)
{
	using namespace boost::multiprecision;
	std::string str = "We live in twilight world, and there are no friends at dusk";

	std::vector<uint8_t> data = {str.begin(), str.end()};

	for (int i = 0 ; i < 200; i++)
	{
		auto rsa = encryption::RSA(256);
		auto enc = rsa.Encrypt(data);
		auto dec = rsa.Decrypt(enc);


		EXPECT_TRUE(str == std::string(dec.begin(), dec.end()));

	}

}
TEST(XOR, ValidEncryptionAndDecryption)
{
	std::string str = "We live in twilight world, and there are no friends at dusk";

	std::vector<uint8_t> data = {str.begin(), str.end()};

	for (int i = 0 ; i < 100; i++)
	{
		const auto key = encryption::xorenc::GenerateKey(64);


		auto enc = encryption::xorenc::Encrypt(data, key);
		auto dec = encryption::xorenc::Decrypt(enc, key);


		EXPECT_TRUE(str == std::string(dec.begin(), dec.end()));

	}
}