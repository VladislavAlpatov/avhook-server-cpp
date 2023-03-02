//
// Created by alpat on 28.01.2023.
//

#include "rsa.h"

#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/integer/mod_inverse.hpp>

#include <boost/random.hpp>
#include <iostream>
#include <array>


using namespace boost::multiprecision;
using namespace boost::random;


bool RSA::IsPrime(cpp_int number)
{
    return miller_rabin_test(number, 25);
}
typedef independent_bits_engine<mt19937, 128, uint128_t> generator_type;

cpp_int GeneratePrimeNumber()
{
    static generator_type gen;

    while (true)
    {
        const auto val = gen();
        if (RSA::IsPrime(val))
            return val;
    }
}

cpp_int generateRandomNumberInRange(cpp_int min, cpp_int max)
{
    // Seed the random number generator
    boost::random::mt19937 gen(time(0));
    boost::random::uniform_int_distribution<cpp_int> dist(min, max);

    // Generate a random number in the given range
    cpp_int n = dist(gen);

    return n;
}

std::pair<RSA::PublicKey, RSA::PrivateKey> RSA::GenerateKeyPair()
{
    auto p = GeneratePrimeNumber();
    auto q = GeneratePrimeNumber();

    auto n = p*q;

    auto phi = (p - 1) * (q - 1);
    cpp_int e;
    do
    {
        e = generateRandomNumberInRange(2, phi-1);
    }
    while (gcd(e, phi) != 1);
    auto d = boost::integer::mod_inverse<cpp_int>(e, phi);

    return {{n,e}, {n,d}};
}

std::vector<unsigned char >  RSA::Encrypt(const RSA::PublicKey &key, const std::string &str)
{
    std::vector<unsigned char> out;
    out.reserve(str.size());

    for (size_t i = 0; i < str.size(); i+= 32)
    {
        auto              szBlockSize = str.size() - i;
        cpp_int           encryptedBlock;

        if (szBlockSize < 32)
        {
            std::array<unsigned char, 32> paddedBlock = {0};
            //memcpy(paddedBlock.data(), str.data() + i, szBlockSize);

            import_bits(encryptedBlock, (unsigned char*)str.data()+i, (unsigned char*)str.data()+i+szBlockSize);
        }
        else
            import_bits(encryptedBlock, str.begin(), str.end());


        encryptedBlock = powm<cpp_int>(encryptedBlock, key.m_NumberEncrypt, key.m_NumberN);

        std::list<unsigned char> encryptedBlockBytes;
        export_bits(encryptedBlock, std::back_inserter(encryptedBlockBytes), 8);

        while (encryptedBlockBytes.size() < 32)
            encryptedBlockBytes.push_front(NULL);

        for (const auto& encryptedByte : encryptedBlockBytes)
            out.push_back(encryptedByte);
    }


    return out;
}

std::string RSA::Decrypt(const RSA::PrivateKey &key, const std::vector<unsigned char> &str)
{
    std::vector<unsigned char> out;
    out.reserve(str.size());

    for (size_t i = 0; i < str.size(); i+= 32)
    {
        auto              szBlockSize = str.size() - i;
        cpp_int           encryptedBlock;

        if (szBlockSize < 32)
        {
            std::array<unsigned char, 32> paddedBlock = {0};
            //memcpy(paddedBlock.data(), str.data() + i, szBlockSize);

            import_bits(encryptedBlock, (unsigned char*)str.data()+i, (unsigned char*)str.data()+i+szBlockSize);
        }
        else
            import_bits(encryptedBlock, str.begin(), str.end());


        encryptedBlock = powm<cpp_int>(encryptedBlock, key.m_NumberDecrypt, key.m_NumberN);

        std::vector<unsigned char> encryptedBlockBytes;
        encryptedBlockBytes.reserve(32);
        export_bits(encryptedBlock, std::back_inserter(encryptedBlockBytes), 8);


        while (encryptedBlockBytes.size() <= 32)
            encryptedBlockBytes.push_back(NULL);

        for (const auto& encryptedByte : encryptedBlockBytes)
            out.push_back(encryptedByte);
    }


    return {(const char*)out.data()};

}
