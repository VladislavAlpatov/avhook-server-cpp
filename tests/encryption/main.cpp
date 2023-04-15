//
// Created by alpat on 10.04.2023.
//
#include <gtest/gtest.h>
#include <RSA.h>
#include <boost/integer/mod_inverse.hpp>
#include <boost/random.hpp>
#include <boost/integer.hpp>

#include <iostream>

// Generate a random prime number using the Miller-Rabin primality test

TEST(DBAPI, RSA_ValidEncryptionAndDecryption)
{
	using namespace boost::multiprecision;
	std::string str = "We live in twilight world, and there are no friends at dusk";

	std::vector<uint8_t> data = {str.begin(), str.end()};

	for (int i = 0 ; i < 200; i++)
	{
		auto rsa = Encryption::RSA(256);
		auto enc = rsa.Encrypt(data);
		auto dec = rsa.Decrypt(enc);


		EXPECT_TRUE(str == std::string(dec.begin(), dec.end()));

	}

}