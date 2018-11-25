#include "cryptopp_ecdh_algorithm.h"

ECDH_Algorithm::ECDH_Algorithm(): m_curve(CryptoPP::ASN1::secp256r1())
{
    m_ecdh.AccessGroupParameters() = m_curve;
    m_private_key.New(m_ecdh.PrivateKeyLength());
    m_pubic_key.New(m_ecdh.PublicKeyLength());
    m_shared.New(m_ecdh.AgreedValueLength());
}

ECDH_Algorithm::ECDH_Algorithm(CryptoPP::OID input_curve):m_curve(input_curve),m_ecdh(input_curve)
{
    m_private_key.New(m_ecdh.PrivateKeyLength());
    m_pubic_key.New(m_ecdh.PublicKeyLength());
    m_shared.New(m_ecdh.AgreedValueLength());
}

void ECDH_Algorithm::SetCurve(CryptoPP::OID input_curve)
{
    m_ecdh.AccessGroupParameters() = input_curve;
    m_private_key.CleanNew(m_ecdh.PrivateKeyLength());
    m_pubic_key.CleanNew(m_ecdh.PublicKeyLength());
    m_shared.CleanNew(m_ecdh.AgreedValueLength());
}

void ECDH_Algorithm::GenerateKeyPair()
{
    m_ecdh.GenerateKeyPair(m_rand_engine, m_private_key, m_pubic_key);
}

std::string ECDH_Algorithm::GetPublicKey()
{
    string str_return(m_pubic_key.begin(),m_pubic_key.end());
    return str_return;
}

std::string ECDH_Algorithm::GetPrivateKey()
{
    string str_return(m_private_key.begin(),m_private_key.end());
    return str_return;
}

std::string ECDH_Algorithm::GetSharedKey()
{
    string str_return(m_shared.begin(),m_shared.end());
    return str_return;
}

std::string ECDH_Algorithm::GetPublicKeyWithBase64()
{
    return Cryptopp_Base64::encode(GetPublicKey());
}

std::string ECDH_Algorithm::GetPrivateKeyWithBase64()
{
    return Cryptopp_Base64::encode(GetPrivateKey());
}

std::string ECDH_Algorithm::GetSharedKeyWithBase64()
{
    return Cryptopp_Base64::encode(GetSharedKey());
}

void ECDH_Algorithm::SetPublicKey(const std::string &input_string)
{
    m_pubic_key.CleanNew(input_string.size());
    m_pubic_key.Assign((CryptoPP::byte *)input_string.data(),input_string.size());
}

void ECDH_Algorithm::SetPrivateKey(const std::string &input_string)
{
    m_private_key.CleanNew(input_string.size());
    m_private_key.Assign((CryptoPP::byte *)input_string.data(),input_string.size());
}

void ECDH_Algorithm::SetPublicKeyWithBase64(const std::string &input_string)
{
    SetPublicKey(Cryptopp_Base64::decode(input_string));
}

void ECDH_Algorithm::SetPrivateKeyWithBase64(const std::string &input_string)
{
    SetPrivateKey(Cryptopp_Base64::decode(input_string));
}

bool ECDH_Algorithm::AgreePublicKey(const std::string &input_string_public_key)
{
    CryptoPP::SecByteBlock other_pubic_key;
    other_pubic_key.CleanNew(input_string_public_key.size());
    other_pubic_key.Assign((CryptoPP::byte *)input_string_public_key.data(),input_string_public_key.size());

    bool bret = m_ecdh.Agree(m_shared,m_private_key,other_pubic_key);
    return bret;
}

bool ECDH_Algorithm::AgreePublicKeyWithBase64(const std::string &input_string_public_key)
{
    return AgreePublicKey(Cryptopp_Base64::decode(input_string_public_key));
}
