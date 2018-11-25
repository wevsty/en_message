#include "cryptopp_hash_algorithm.h"

#ifdef _MSC_VER
#pragma  warning(push)
#pragma  warning(disable:4251 4275 4101)
#include "cryptopp_dll_init.h"
#endif

std::string CalcStringSHA256(const std::string &raw_data)
{
    std::string hash;
    try
    {
        CryptoPP::SHA256 sha256;
        CryptoPP::StringSource(raw_data, true
            , new CryptoPP::HashFilter(sha256
                ,new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))
                                       )
                               );
    }
    catch(...)
    {
        hash.clear();
    }
	return hash;
}

std::string CalcFileSHA256(const std::string &filepath)
{
    std::string hash;
    try
    {
        CryptoPP::SHA256 sha256;
        CryptoPP::FileSource(filepath.c_str(), true
            , new CryptoPP::HashFilter(sha256
                ,new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))
                                       )
                               );
    }
    catch(...)
    {
        hash.clear();
    }
    return hash;
}

#ifdef _MSC_VER
#pragma  warning(  pop  )
#endif

