#ifndef EDCH_ALGORITHM_H
#define EDCH_ALGORITHM_H

//#include "cryptopp_dll_init.h"

#include <string>
using std::string;

#include <stdexcept>
using std::runtime_error;

#include <cstdlib>
using std::exit;

#include "cryptopp_encoder.h"

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;
using CryptoPP::AutoSeededX917RNG;

#include "cryptopp/aes.h"
using CryptoPP::AES;

#include "cryptopp/eccrypto.h"
using CryptoPP::ECP;
using CryptoPP::ECDH;

#include "cryptopp/secblock.h"
using CryptoPP::SecByteBlock;

#include "cryptopp/oids.h"
using CryptoPP::OID;

// ASN1 is a namespace, not an object
#include "cryptopp/asn.h"
using namespace CryptoPP::ASN1;

#include "cryptopp/integer.h"
using CryptoPP::Integer;



class ECDH_Algorithm
{
public:
    CryptoPP::AutoSeededRandomPool m_rand_engine;
    CryptoPP::OID m_curve;
    CryptoPP::ECDH < CryptoPP::ECP >::Domain m_ecdh;
    CryptoPP::SecByteBlock m_private_key;
    CryptoPP::SecByteBlock m_pubic_key;
    CryptoPP::SecByteBlock m_shared;

    ECDH_Algorithm();
    ECDH_Algorithm(CryptoPP::OID input_curve);
    void SetCurve(CryptoPP::OID input_curve);
    void GenerateKeyPair();
    //get
    std::string GetPublicKey();
    std::string GetPrivateKey();
    std::string GetSharedKey();
    std::string GetPublicKeyWithBase64();
    std::string GetPrivateKeyWithBase64();
    std::string GetSharedKeyWithBase64();
    //set
    void SetPublicKey(const std::string &input_string);
    void SetPrivateKey(const std::string &input_string);
    void SetPublicKeyWithBase64(const std::string &input_string);
    void SetPrivateKeyWithBase64(const std::string &input_string);
    //calc
    bool AgreePublicKey(const std::string &input_string_public_key);
    bool AgreePublicKeyWithBase64(const std::string &input_string_public_key);
};

#endif // EDCH_ALGORITHM_H
