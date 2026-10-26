#include <gtest/gtest.h>

extern "C"
{
#include "crypto.h"
}

TEST(CryptoTest, SaltGeneration)
{
    char salt[17];

    generateSalt(salt);

    EXPECT_EQ(strlen(salt), 16);
}

TEST(CryptoTest, SHA256HashGeneration)
{
    char hash[65];

    sha256String("test123", hash);

    EXPECT_EQ(strlen(hash), 64);
}

TEST(CryptoTest, AESEncryptionDecryption)
{
    const unsigned char key[16] =
    {
        'A','E','S','K',
        'E','Y','1','2',
        '3','4','5','6',
        '7','8','9','0'
    };

    unsigned char plaintext[] =
        "HelloBanking";

    unsigned char ciphertext[128];
    unsigned char decrypted[128];

    int cipherLen =
        encryptAES(
            plaintext,
            strlen((char*)plaintext),
            key,
            ciphertext
        );

    decryptAES(
        ciphertext,
        cipherLen,
        key,
        decrypted
    );

    EXPECT_STREQ(
        (char*)plaintext,
        (char*)decrypted
    );
}