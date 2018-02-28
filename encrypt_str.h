#ifndef ENCRYPT_STR_H
#define ENCRYPT_STR_H
#include <QApplication>
#include <QString>
#include <string>
#include <exception>

//QString decrypt(const QString &password);
//QString encrypt(const QString &password);

std::string AES_ECB_encrypt(std::string sKey, std::string plainText);
std::string AES_ECB_decrypt(std::string sKey, std::string cipherText);

std::string AES_CFB_encrypt(std::string sKey,std::string sIV, std::string plainText);
std::string AES_CFB_decrypt(std::string sKey,std::string sIV, std::string cipherText);
#endif // ENCRYPT_STR_H
