#ifndef CRYPTO_H
#define CRYPTO_H

#include "models.h"

#define AES_KEY_SIZE 16
#define AES_BLOCK_SIZE 16

void generateSalt(char *salt);

void sha256String(
    const char *input,
    char output[HASH_LENGTH]
);

int encryptAES(
    const unsigned char *plaintext,
    int plaintextLen,
    const unsigned char *key,
    unsigned char *ciphertext
);

int decryptAES(
    const unsigned char *ciphertext,
    int ciphertextLen,
    const unsigned char *key,
    unsigned char *plaintext
);

#endif