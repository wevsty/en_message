#ifndef CRYPTOPP_MYSELF_CLASS_BASE64_H
#define CRYPTOPP_MYSELF_CLASS_BASE64_H

//#include "cryptopp_dll_init.h"

#include <cstddef>
#include <string>

#include <cryptopp/config.h>
//using CryptoPP::byte;
//using CryptoPP::word64;

#include <cryptopp/base64.h>
//using CryptoPP::Base64Decoder;
//using CryptoPP::Base64Encoder;

#include "cryptopp/hex.h"
//using CryptoPP::HexEncoder;
//using CryptoPP::HexDecoder;


class Cryptopp_Base64
{
public:
    Cryptopp_Base64();

    static std::string encode(const char* p_data,
                              size_t n_size,
                              bool insertLineBreaks = true,
                              int maxLineLength = 72);
    static std::string encode(const std::string &input_string,
                              bool insertLineBreaks = true,
                              int maxLineLength = 72);

    static std::string decode(const char* p_data,size_t n_size);
    static std::string decode(const std::string &input_string);
};

class Cryptopp_Hex
{
public:
    Cryptopp_Hex();

    static std::string encode(const char* p_data,size_t n_size);
    static std::string encode(const std::string &input_string);

    static std::string decode(const char* p_data,size_t n_size);
    static std::string decode(const std::string &input_string);
};
#endif // CRYPTOPP_MYSELF_CLASS_BASE64_H
