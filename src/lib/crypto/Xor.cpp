//
// Created by alpat on 06.04.2023.
//
#include <vector>


namespace Encryption::Xor
{
    void ApplyXorEncryption(std::vector<u_int8_t>& data,const std::vector<u_int8_t>& key )
    {
        const auto dataLength = data.size();
        const auto keySize    = key.size();


        for (size_t i = 0; i < dataLength; i++)
            data[i] ^= key[i % keySize];
    }
}
