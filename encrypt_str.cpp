#include "encrypt_str.h"

#ifdef _MSC_VER
typedef unsigned char byte;
#pragma  warning(push)
#pragma  warning(disable:4251 4275 4101)
#include "cryptopp_dll_init.h"
#endif

#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
//#include <cryptopp/sha.h>
//#include <cryptopp/md5.h>

//using namespace CryptoPP;
//using std::string;



std::string AES_ECB_encrypt(std::string sKey, std::string plainText)
{
	std::string outstr;
	//填key
	CryptoPP::SecByteBlock key(CryptoPP::AES::MAX_KEYLENGTH);
	memset(key, 0xec, key.size());
	if (sKey.size() <= CryptoPP::AES::MAX_KEYLENGTH)
	{
		memcpy(key, sKey.c_str(), sKey.size());
	}
	else
	{
		memcpy(key, sKey.c_str(), CryptoPP::AES::MAX_KEYLENGTH);
	}
	try
	{
		CryptoPP::AES::Encryption aes_encryption((byte *)key,
			CryptoPP::AES::MAX_KEYLENGTH);
		CryptoPP::ECB_Mode_ExternalCipher::Encryption ecb_encryption(aes_encryption);
		CryptoPP::StreamTransformationFilter ecb_encryptor(ecb_encryption
			, new CryptoPP::HexEncoder(new CryptoPP::StringSink(outstr)));
		ecb_encryptor.Put((byte *)plainText.c_str(), plainText.size());
		ecb_encryptor.MessageEnd();
	}
	catch (std::exception &e)
	{
		// ...
		outstr = "encrypt error";
	}
	catch (...)
	{
		// ...
	}
	return outstr;
}

std::string AES_ECB_decrypt(std::string sKey, std::string cipherText)
{
	std::string outstr;
	//填key
	CryptoPP::SecByteBlock key(CryptoPP::AES::MAX_KEYLENGTH);
	memset(key, 0xec, key.size());
	if (sKey.size() <= CryptoPP::AES::MAX_KEYLENGTH)
	{
		memcpy(key, sKey.c_str(), sKey.size());
	}
	else
	{
		memcpy(key, sKey.c_str(), CryptoPP::AES::MAX_KEYLENGTH);
	}
	try
	{
		CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption ecbDecryption((byte *)key,
			CryptoPP::AES::MAX_KEYLENGTH);
		CryptoPP::HexDecoder decryptor(new CryptoPP::StreamTransformationFilter(
			ecbDecryption
			, new CryptoPP::StringSink(outstr)));
		decryptor.Put((byte *)cipherText.c_str(), cipherText.size());
		decryptor.MessageEnd();
	}
	catch (std::exception &e)
	{
		// ...
		outstr = "decrypt error";
	}
	catch (...)   // ...
	{
	}
	return outstr;
}

std::string AES_CFB_encrypt(std::string sKey, std::string sIV,
	std::string plainText)
{
	std::string outstr;
	//填key
	CryptoPP::SecByteBlock key(CryptoPP::AES::MAX_KEYLENGTH);
	memset(key, 0xec, key.size());
	if (sKey.size() <= CryptoPP::AES::MAX_KEYLENGTH)
	{
		memcpy(key, sKey.c_str(), sKey.size());
	}
	else
	{
		memcpy(key, sKey.c_str(), CryptoPP::AES::MAX_KEYLENGTH);
	}
	//填iv
	byte iv[CryptoPP::AES::BLOCKSIZE];
	memset(iv, 0xec, CryptoPP::AES::BLOCKSIZE);
	if (sIV.size() <= CryptoPP::AES::BLOCKSIZE)
	{
		memcpy(key, sIV.c_str(), sIV.size());
	}
	else
	{
		memcpy(key, sIV.c_str(), CryptoPP::AES::BLOCKSIZE);
	}
	try
	{
		CryptoPP::AES::Encryption aes_encryption((byte *)key,
			CryptoPP::AES::MAX_KEYLENGTH);
		CryptoPP::CFB_Mode_ExternalCipher::Encryption cfb_encryption(aes_encryption,
			iv);
		CryptoPP::StreamTransformationFilter cfb_encryptor(cfb_encryption
			, new CryptoPP::HexEncoder(new CryptoPP::StringSink(outstr)));
		cfb_encryptor.Put((byte *)plainText.c_str(), plainText.size());
		cfb_encryptor.MessageEnd();
	}
	catch (std::exception &e)
	{
		// ...
		outstr = "encrypt error";
	}
	catch (...)
	{
		// ...
	}
	return outstr;
}

std::string AES_CFB_decrypt(std::string sKey, std::string sIV,
	std::string cipherText)
{
	std::string outstr;
	//填key
	CryptoPP::SecByteBlock key(CryptoPP::AES::MAX_KEYLENGTH);
	memset(key, 0xec, key.size());
	if (sKey.size() <= CryptoPP::AES::MAX_KEYLENGTH)
	{
		memcpy(key, sKey.c_str(), sKey.size());
	}
	else
	{
		memcpy(key, sKey.c_str(), CryptoPP::AES::MAX_KEYLENGTH);
	}
	//填iv
	byte iv[CryptoPP::AES::BLOCKSIZE];
	memset(iv, 0xec, CryptoPP::AES::BLOCKSIZE);
	if (sIV.size() <= CryptoPP::AES::BLOCKSIZE)
	{
		memcpy(key, sIV.c_str(), sIV.size());
	}
	else
	{
		memcpy(key, sIV.c_str(), CryptoPP::AES::BLOCKSIZE);
	}
	try
	{
		CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption CFB_Decryption((byte *)key,
			CryptoPP::AES::MAX_KEYLENGTH, iv);
		CryptoPP::HexDecoder decryptor(new CryptoPP::StreamTransformationFilter(
			CFB_Decryption
			, new CryptoPP::StringSink(outstr)));
		decryptor.Put((byte *)cipherText.c_str(), cipherText.size());
		decryptor.MessageEnd();
	}
	catch (std::exception &e)
	{
		// ...
		outstr = "decrypt error";
	}
	catch (...)   // ...
	{
	}
	return outstr;
}

#ifdef _MSC_VER
#pragma  warning(  pop  )
#endif