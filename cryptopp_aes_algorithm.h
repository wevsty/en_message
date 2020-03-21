#ifndef CRYPTOPP_AES_ALGORITHM_H
#define CRYPTOPP_AES_ALGORITHM_H

#include <string>
#include <cstdlib>
#include <exception>

/*----------------CryptoPP----------------*/
#ifdef _MSC_VER
#pragma  warning(push)
#pragma  warning(disable:4251 4275 4101)
//#include "cryptopp_dll_init.h"
#endif

#include "cryptopp/config.h"
//using CryptoPP::byte;
//using CryptoPP::word64;

#include "cryptopp/default.h"
#include "cryptopp/osrng.h"
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/filters.h"
#include "cryptopp/files.h"
//#include "cryptopp/hex.h"
//#include "cryptopp/sha.h"
//#include "cryptopp/md5.h"

/*----------------CryptoPP----------------*/
#include "unused_macro.h"

class AES_256_CFB_Algorithm
{
public:
    enum{
        AES_256_CFB_MAX_KEY_SIZE = CryptoPP::AES::MAX_KEYLENGTH,
        AES_256_CFB_MAX_IV_SIZE = CryptoPP::AES::BLOCKSIZE
    };

    enum{
        KeySize = CryptoPP::AES::MAX_KEYLENGTH,
        IvSize = CryptoPP::AES::BLOCKSIZE
    };
    //static constexpr const size_t KeySize = CryptoPP::AES::MAX_KEYLENGTH;
    //static constexpr const size_t IvSize = CryptoPP::AES::BLOCKSIZE;

    AES_256_CFB_Algorithm();
    ~AES_256_CFB_Algorithm();

    void GenerateIv();
    void GenerateKey();

    void SetKey(const std::string &input_key_data);
    void SetIv(const std::string &input_iv_data);

    std::string GetKey();
    std::string GetIv();

    bool EncryptString(const std::string &input_string,std::string &output_string);
    bool DecryptString(const std::string &input_string,std::string &output_string);

    bool EncryptFile(const std::string &input_string_path,const std::string &output_string_path);
    bool DecryptFile(const std::string &input_string_path,const std::string &output_string_path);

    bool EncryptInit();
    bool EncryptProcessData(char *outString,size_t OutLength, const char *inString, size_t InLength);

    bool DecryptInit();
    bool DecryptProcessData(char *outString,size_t OutLength, const char *inString, size_t InLength);

private:

    CryptoPP::AutoSeededRandomPool m_rand_engine;
    CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption m_encrypt_engine;
    CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption m_decrypt_engine;
    CryptoPP::SecByteBlock m_key;
    CryptoPP::SecByteBlock m_iv;
};

#ifdef _MSC_VER
#pragma  warning(  pop  )
#endif

#endif // CRYPTOPP_AES_ALGORITHM_H
