# en_message

一个加密文字的小工具，与朋友协商好密钥后你可以使用它来加密任何文字信息，保证通信安全。

加密使用Crypto++库中提供的AES算法（AES-256-CFB）。

密钥交换功能采用Crypto++库中提供的ECDH算法（ECDH/secp256k1）进行密钥交换。


## 编译依赖

Qt 5.11.2

Crypto++ Library 7.0


### Crypto++ Library Install

On Ubuntu you can used apt install Crypto++
```
apt install libcrypto++-utils libcrypto++-dev
```

On Others

plase vist https://www.cryptopp.com/