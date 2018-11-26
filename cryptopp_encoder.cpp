#include "cryptopp_encoder.h"

Cryptopp_Base64::Cryptopp_Base64()
{

}

std::string Cryptopp_Base64::encode(const char *p_data, size_t n_size,
                                    bool insertLineBreaks,
                                    int maxLineLength)
{
    std::string encoded;

    CryptoPP::Base64Encoder encoder(NULL,insertLineBreaks,maxLineLength);
    encoder.Put((const CryptoPP::byte*)p_data, n_size);
    encoder.MessageEnd();

    CryptoPP::word64 size = encoder.MaxRetrievable();
    if(size)
    {
        encoded.resize(size);
        encoder.Get((CryptoPP::byte*)&encoded[0], encoded.size());
    }

    return encoded;
}

std::string Cryptopp_Base64::encode(const std::string &input_string,
                                    bool insertLineBreaks,
                                    int maxLineLength)
{
    std::string encoded;

    CryptoPP::Base64Encoder encoder(NULL,insertLineBreaks,maxLineLength);
    encoder.Put((const CryptoPP::byte*)input_string.data(), input_string.size());
    encoder.MessageEnd();

    CryptoPP::word64 size = encoder.MaxRetrievable();
    if(size)
    {
        encoded.resize(size);
        encoder.Get((CryptoPP::byte*)&encoded[0], encoded.size());
    }

    return encoded;
}

std::string Cryptopp_Base64::decode(const char *p_data, size_t n_size)
{
    std::string decoded;

    CryptoPP::Base64Decoder decoder;
    decoder.Put( (const CryptoPP::byte*)p_data, n_size);
    decoder.MessageEnd();

    CryptoPP::word64 size = decoder.MaxRetrievable();
    if(size && size <= SIZE_MAX)
    {
        decoded.resize(size);
        decoder.Get((CryptoPP::byte*)&decoded[0], decoded.size());
    }
    return decoded;
}

std::string Cryptopp_Base64::decode(const std::string &input_string)
{
    std::string decoded;

    CryptoPP::Base64Decoder decoder;
    decoder.Put( (const CryptoPP::byte*)input_string.data(), input_string.size() );
    decoder.MessageEnd();

    CryptoPP::word64 size = decoder.MaxRetrievable();
    if(size && size <= SIZE_MAX)
    {
        decoded.resize(size);
        decoder.Get((CryptoPP::byte*)&decoded[0], decoded.size());
    }
    return decoded;
}


Cryptopp_Hex::Cryptopp_Hex()
{

}

std::string Cryptopp_Hex::encode(const char *p_data, size_t n_size)
{
    std::string encoded;

    CryptoPP::HexEncoder encoder;
    encoder.Put((const CryptoPP::byte*)p_data, n_size);
    encoder.MessageEnd();

    CryptoPP::word64 size = encoder.MaxRetrievable();
    if(size)
    {
        encoded.resize(size);
        encoder.Get((CryptoPP::byte*)&encoded[0], encoded.size());
    }

    return encoded;
}

std::string Cryptopp_Hex::encode(const std::string &input_string)
{
    std::string encoded;

    CryptoPP::HexEncoder encoder;
    encoder.Put((const CryptoPP::byte*)input_string.data(), input_string.size());
    encoder.MessageEnd();

    CryptoPP::word64 size = encoder.MaxRetrievable();
    if(size)
    {
        encoded.resize(size);
        encoder.Get((CryptoPP::byte*)&encoded[0], encoded.size());
    }

    return encoded;
}

std::string Cryptopp_Hex::decode(const char *p_data, size_t n_size)
{
    std::string decoded;

    CryptoPP::HexDecoder decoder;
    decoder.Put( (const CryptoPP::byte*)p_data, n_size);
    decoder.MessageEnd();

    CryptoPP::word64 size = decoder.MaxRetrievable();
    if(size && size <= SIZE_MAX)
    {
        decoded.resize(size);
        decoder.Get((CryptoPP::byte*)&decoded[0], decoded.size());
    }
    return decoded;
}

std::string Cryptopp_Hex::decode(const std::string &input_string)
{
    std::string decoded;

    CryptoPP::HexDecoder decoder;
    decoder.Put( (const CryptoPP::byte*)input_string.data(), input_string.size() );
    decoder.MessageEnd();

    CryptoPP::word64 size = decoder.MaxRetrievable();
    if(size && size <= SIZE_MAX)
    {
        decoded.resize(size);
        decoder.Get((CryptoPP::byte*)&decoded[0], decoded.size());
    }
    return decoded;
}
