#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <openssl/sha.h>
#include <openssl/evp.h>

#include "crypto.h"

void generateSalt(char *salt)
{
    const char charset[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";

    int length = 16;

    srand((unsigned int)time(NULL));

    for(int i = 0; i < length; i++)
    {
        salt[i] = charset[rand() % 62];
    }

    salt[length] = '\0';
}

void sha256String(
    const char *input,
    char output[HASH_LENGTH]
)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(
        (const unsigned char *)input,
        strlen(input),
        hash
    );

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(
            output + (i * 2),
            "%02x",
            hash[i]
        );
    }

    output[64] = '\0';
}

int encryptAES(
    const unsigned char *plaintext,
    int plaintextLen,
    const unsigned char *key,
    unsigned char *ciphertext
)
{
    EVP_CIPHER_CTX *ctx;

    int len;
    int cipherLen;

    ctx = EVP_CIPHER_CTX_new();

    EVP_EncryptInit_ex(
        ctx,
        EVP_aes_128_ecb(),
        NULL,
        key,
        NULL
    );

    EVP_EncryptUpdate(
        ctx,
        ciphertext,
        &len,
        plaintext,
        plaintextLen
    );

    cipherLen = len;

    EVP_EncryptFinal_ex(
        ctx,
        ciphertext + len,
        &len
    );

    cipherLen += len;

    EVP_CIPHER_CTX_free(ctx);

    return cipherLen;
}

int decryptAES(
    const unsigned char *ciphertext,
    int ciphertextLen,
    const unsigned char *key,
    unsigned char *plaintext
)
{
    EVP_CIPHER_CTX *ctx;

    int len;
    int plainLen;

    ctx = EVP_CIPHER_CTX_new();

    EVP_DecryptInit_ex(
        ctx,
        EVP_aes_128_ecb(),
        NULL,
        key,
        NULL
    );

    EVP_DecryptUpdate(
        ctx,
        plaintext,
        &len,
        ciphertext,
        ciphertextLen
    );

    plainLen = len;

    EVP_DecryptFinal_ex(
        ctx,
        plaintext + len,
        &len
    );

    plainLen += len;

    EVP_CIPHER_CTX_free(ctx);

    plaintext[plainLen] = '\0';

    return plainLen;
}