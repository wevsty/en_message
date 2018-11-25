#ifndef CRYPTOPP_HASH_ALGORITHM_H
#define CRYPTOPP_HASH_ALGORITHM_H

#include <string>
#include "cryptopp/config.h"
#include "cryptopp/filters.h"
#include "cryptopp/files.h"
#include "cryptopp/hex.h"
#include "cryptopp/sha.h"

std::string CalcStringSHA256(const std::string &raw_data);
std::string CalcFileSHA256(const std::string &filepath);
#endif // CRYPTOPP_HASH_ALGORITHM_H
