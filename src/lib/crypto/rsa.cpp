//
// Created by alpat on 28.01.2023.
//

#include "rsa.h"

#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/integer/mod_inverse.hpp>

#include <boost/random.hpp>
#include <iostream>

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
    auto enc = powm<cpp_int>(1, e, n);
    auto dec = (int) powm<cpp_int>(enc, d, n);
    std::cout << n << '\n' << (uint256_t)n;
    return {{n,e}, {n,d}};
}

std::vector<cpp_int>  RSA::Encrypt(const RSA::PublicKey &key, const std::string &str)
{
    std::vector<cpp_int> out;
    out.reserve(str.size());
    for (const auto chr : str)
        out.push_back(powm<cpp_int>(chr, key.m_NumberEncrypt, key.m_NumberN));

    return out;
}

std::string RSA::Decrypt(const RSA::PrivateKey &key, const std::vector<boost::multiprecision::cpp_int> &str)
{
    std::string out;
    out.reserve(str.size());

    for (const auto& encChar : str)
        out.push_back((char)powm<cpp_int>(encChar, key.m_NumberDecrypt, key.m_NumberN));

}
