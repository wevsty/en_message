# en_message

一个加密文字的小工具，与朋友协商好密钥后你可以使用它来加密任何文字信息，保证通信安全。

加密使用Crypto++库中提供的AES算法（AES-256-CFB）。

密钥交换功能采用Crypto++库中提供的ECDH算法（ECDH/secp256k1）进行密钥交换。

如需要验证通讯双方身份，建议搭配GPG来使用。


## 编译依赖

Qt 5.14.1

Crypto++ Library 8.2

## 支持平台
Windows Linux(需要自行编译)

### About Crypto++ Library
plase vist https://www.cryptopp.com/