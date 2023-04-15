//
// Created by alpat on 06.04.2023.
//

#pragma once
#include <vector>

namespace Encryption::Xor
{
	std::vector<u_int8_t> Encrypt(std::vector<u_int8_t> data,const std::vector<u_int8_t>& key );
}