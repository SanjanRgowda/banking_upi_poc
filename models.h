#ifndef MODELS_H
#define MODELS_H

#define MAX_USERNAME 50
#define HASH_LENGTH 65
#define SALT_LENGTH 17

typedef struct
{
    int userId;

    char username[MAX_USERNAME];

    char salt[SALT_LENGTH];

    char passwordHash[HASH_LENGTH];

    char role[20];

} User;

typedef struct
{
    int transactionId;

    char sender[50];

    char receiver[50];

    double amount;

    char cipherText[512];

    char integrityHash[HASH_LENGTH];

} Transaction;

typedef struct TransactionNode
{
    Transaction data;

    struct TransactionNode *next;

} TransactionNode;

#endif