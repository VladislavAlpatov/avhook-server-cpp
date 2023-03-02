//
// Created by alpat on 28.01.2023.
//

#pragma once
#include <boost/multiprecision/cpp_int.hpp>


namespace RSA
{
    class PrivateKey
    {
    public:
        PrivateKey(const boost::multiprecision::cpp_int& n, boost::multiprecision::cpp_int& d)
        {
            m_NumberN = n;
            m_NumberDecrypt = d;
        }
        boost::multiprecision::cpp_int m_NumberN;
        boost::multiprecision::cpp_int m_NumberDecrypt;

    };
    class PublicKey
    {
    public:
        PublicKey(const boost::multiprecision::cpp_int& n, boost::multiprecision::cpp_int& e)
        {
            m_NumberN = n;
            m_NumberEncrypt = e;
        }
        boost::multiprecision::cpp_int m_NumberN;
        boost::multiprecision::cpp_int m_NumberEncrypt;
    };


    bool IsPrime(boost::multiprecision::cpp_int number);
    std::pair<PublicKey, PrivateKey> GenerateKeyPair();
    std::vector<boost::multiprecision::cpp_int> Encrypt(const PublicKey& key, const std::string& str);
    std::string Decrypt(const PrivateKey& key,const std::vector<boost::multiprecision::cpp_int> & str);
} // crypto

