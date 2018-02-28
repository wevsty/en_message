#include "hash_str.h"

#ifdef _MSC_VER
typedef unsigned char byte;
#pragma  warning(push) 
#pragma  warning(disable:4251 4275 4101)
#include <cryptopp/dll.h>
#endif

#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
//#include <crypto++/md5.h>

std::string calc_SHA256(std::string raw_data)
{
  CryptoPP::SHA256 sha256;
  std::string hash = "";
  CryptoPP::StringSource(raw_data
                         , true
                         , new CryptoPP::HashFilter(sha256, new CryptoPP::HexEncoder(new CryptoPP::StringSink(hash))));
  return hash;
}

#ifdef _MSC_VER
#pragma  warning(  pop  ) 
#endif