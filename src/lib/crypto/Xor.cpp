//
// Created by alpat on 06.04.2023.
//
#include <vector>
#include "Xor.h"
#include <boost/range/adaptor/reversed.hpp>
#include <boost/random.hpp>

namespace encryption::xor_enc
{
	std::vector<uint8_t> Encrypt(std::vector<uint8_t> data,const std::vector<uint8_t>& key )
    {
        for (auto& byte : data)
			for (auto& keyByte : key)
				byte ^= keyByte;

		return data;
    }

	std::vector<uint8_t> Decrypt(std::vector<uint8_t> data, const std::vector<uint8_t>& key)
	{
		for (auto& byte : data)
			for (auto& keyByte : boost::adaptors::reverse(key))
				byte ^= keyByte;

		return data;
	}

	std::vector<uint8_t> GenerateKey(std::size_t byteLength)
	{
		std::vector<uint8_t> key;
		key.reserve(byteLength);

		static boost::random::mt19937 gen(time(0));
		static boost::random::uniform_int_distribution<uint8_t> dist(1, 255);

		for (size_t i = 0; i < byteLength; i++)
			key.push_back(dist(gen));

		return key;
	}
}
