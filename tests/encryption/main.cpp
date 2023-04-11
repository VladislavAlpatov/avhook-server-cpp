//
// Created by alpat on 10.04.2023.
//
#include <gtest/gtest.h>
#include <RSA.h>


TEST(DBAPI, RSA_ValidEncryptionAndDecryption)
{

	for (int i = 0 ; i < 20; i++)
	{
		auto rsa = Encryption::RSA(1024);
		std::string original = "We live in a twilight world and there are no friends in the dusk";
		const auto encrypted = rsa.Encrypt({original.begin(), original.end()});
		const auto decrypted = rsa.Decrypt(encrypted);
		const auto decrypted_str = std::string(decrypted.begin(), decrypted.end());

		EXPECT_TRUE(original == decrypted_str);
	}

}