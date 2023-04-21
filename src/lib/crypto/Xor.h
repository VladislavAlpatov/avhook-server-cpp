//
// Created by alpat on 06.04.2023.
//

#pragma once
#include <vector>
#include <cstdint>

namespace Encryption::Xor
{
	[[nodiscard]] std::vector<uint8_t> Encrypt(std::vector<uint8_t> data,const std::vector<uint8_t>& key );
	[[nodiscard]] std::vector<uint8_t> Decrypt(std::vector<uint8_t> data,const std::vector<uint8_t>& key );
	[[nodiscard]] std::vector<uint8_t> GenerateKey(size_t byteLength);
}