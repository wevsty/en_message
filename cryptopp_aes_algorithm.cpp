#include "cryptopp_aes_algorithm.h"


AES_256_CFB_Algorithm::AES_256_CFB_Algorithm()
{
    m_key.New(AES_256_CFB_MAX_KEY_SIZE);
    m_iv.New(AES_256_CFB_MAX_IV_SIZE);

    m_rand_engine.GenerateBlock(m_key.BytePtr(), m_key.size());
    m_rand_engine.GenerateBlock(m_iv.BytePtr(), m_iv.size());
}

AES_256_CFB_Algorithm::~AES_256_CFB_Algorithm()
{

}

void AES_256_CFB_Algorithm::GenerateIv()
{
    m_rand_engine.GenerateBlock(m_iv.BytePtr(), m_iv.size());

}

void AES_256_CFB_Algorithm::GenerateKey()
{
    m_rand_engine.GenerateBlock(m_key.BytePtr(), m_key.size());
}

void AES_256_CFB_Algorithm::SetKey(const std::string &input_key_data)
{
    std::string key_data = input_key_data;
    key_data.resize(AES_256_CFB_MAX_KEY_SIZE);
    CryptoPP::byte* ptr_byte_key = m_key.BytePtr();
    memcpy(ptr_byte_key,key_data.data(),key_data.size());
}

void AES_256_CFB_Algorithm::SetIv(const std::string &input_iv_data)
{
    std::string iv_data = input_iv_data;
    iv_data.resize(AES_256_CFB_MAX_IV_SIZE);
    CryptoPP::byte* ptr_byte_key = m_iv.BytePtr();
    memcpy(ptr_byte_key,iv_data.data(),iv_data.size());
}

std::string AES_256_CFB_Algorithm::GetKey()
{
    std::string str_return(m_key.begin(),m_key.end());
    return str_return;
}

std::string AES_256_CFB_Algorithm::GetIv()
{
    std::string str_return(m_iv.begin(),m_iv.end());
    return str_return;
}

bool AES_256_CFB_Algorithm::EncryptString(const std::string &input_string, std::string &output_string)
{
    try
    {
        m_encrypt_engine.SetKeyWithIV(m_key.BytePtr(),m_key.size(),m_iv.BytePtr(),m_iv.size());
        CryptoPP::StringSource(input_string, true,
            new CryptoPP::StreamTransformationFilter(m_encrypt_engine,
                new CryptoPP::StringSink(output_string)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch(const CryptoPP::Exception& e)
    {
        //cerr << e.what() << endl;
        //exit(1);
        UNUSED_VARIANT(e);
        return false;
    }
    catch(...)
    {
        return false;
    }
    return true;
}

bool AES_256_CFB_Algorithm::DecryptString(const std::string &input_string, std::string &output_string)
{
    try
    {
        m_decrypt_engine.SetKeyWithIV(m_key.BytePtr(),m_key.size(),m_iv.BytePtr(),m_iv.size());
        CryptoPP::StringSource(input_string, true,
            new CryptoPP::StreamTransformationFilter(m_decrypt_engine,
                new CryptoPP::StringSink(output_string)
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch(const CryptoPP::Exception& e)
    {
        //cerr << e.what() << endl;
        //exit(1);
        UNUSED_VARIANT(e);
        return false;
    }
    catch(...)
    {
        return false;
    }
    return true;
}

bool AES_256_CFB_Algorithm::EncryptFile(const std::string &input_string_path, const std::string &output_string_path)
{
    try
    {
        m_encrypt_engine.SetKeyWithIV(m_key.BytePtr(),m_key.size(),m_iv.BytePtr(),m_iv.size());
        CryptoPP::FileSource(input_string_path.c_str(), true,
            new CryptoPP::StreamTransformationFilter(m_encrypt_engine,
                new CryptoPP::FileSink(output_string_path.c_str())
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch(const CryptoPP::Exception& e)
    {
        //cerr << e.what() << endl;
        //exit(1);
        UNUSED_VARIANT(e);
        return false;
    }
    catch(...)
    {
        return false;
    }
    return true;
}

bool AES_256_CFB_Algorithm::DecryptFile(const std::string &input_string_path, const std::string &output_string_path)
{
    try
    {
        m_decrypt_engine.SetKeyWithIV(m_key.BytePtr(),m_key.size(),m_iv.BytePtr(),m_iv.size());
        CryptoPP::FileSource(input_string_path.c_str(), true,
            new CryptoPP::StreamTransformationFilter(m_decrypt_engine,
                new CryptoPP::FileSink(output_string_path.c_str())
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch(const CryptoPP::Exception& e)
    {
        //cerr << e.what() << endl;
        //exit(1);
        UNUSED_VARIANT(e);
        return false;
    }
    catch(...)
    {
        return false;
    }
    return true;
}

bool AES_256_CFB_Algorithm::EncryptInit()
{
    m_encrypt_engine.SetKeyWithIV(m_key.BytePtr(),m_key.size(),m_iv.BytePtr(),m_iv.size());
    return true;
}

bool AES_256_CFB_Algorithm::EncryptProcessData(char *outString,size_t OutLength, const char *inString, size_t InLength)
{
    //AES-256-CFB是流式算法，不需要进行块填充
    if(OutLength !=InLength)
    {
        return false;
    }
    m_encrypt_engine.ProcessData(
                reinterpret_cast<CryptoPP::byte*>(outString),
                reinterpret_cast<const CryptoPP::byte*>(inString),
                OutLength);
    return true;
}

bool AES_256_CFB_Algorithm::DecryptInit()
{
    m_decrypt_engine.SetKeyWithIV(m_key.BytePtr(),m_key.size(),m_iv.BytePtr(),m_iv.size());
    return true;
}

bool AES_256_CFB_Algorithm::DecryptProcessData(char *outString, size_t OutLength, const char *inString, size_t InLength)
{
    //AES-256-CFB是流式算法，不需要进行块填充
    if(OutLength !=InLength)
    {
        return false;
    }
    m_decrypt_engine.ProcessData(
                reinterpret_cast<CryptoPP::byte*>(outString),
                reinterpret_cast<const CryptoPP::byte*>(inString),
                OutLength);
    return true;
}


