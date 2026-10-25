#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "transaction.h"
#include "crypto.h"

TransactionNode *head = NULL;

/* AES-128 Key */
static const unsigned char AES_KEY[16] =
{
    'A','E','S','K',
    'E','Y','1','2',
    '3','4','5','6',
    '7','8','9','0'
};

static void addTransactionNode(
    Transaction transaction
)
{
    TransactionNode *newNode;

    newNode =
        (TransactionNode*)malloc(
            sizeof(TransactionNode)
        );

    if(newNode == NULL)
    {
        printf("Memory Allocation Failed\n");
        return;
    }

    newNode->data = transaction;
    newNode->next = NULL;

    if(head == NULL)
    {
        head = newNode;
    }
    else
    {
        TransactionNode *temp = head;

        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

void createTransaction(void)
{
    Transaction transaction;

    FILE *fp;

    char plainData[256];

    unsigned char cipherText[512];

    int cipherLength;

    printf("Transaction ID: ");
    scanf("%d",
          &transaction.transactionId);

    printf("Sender: ");
    scanf("%49s",
          transaction.sender);

    printf("Receiver: ");
    scanf("%49s",
          transaction.receiver);

    printf("Amount: ");
    scanf("%lf",
          &transaction.amount);

    snprintf(
        plainData,
        sizeof(plainData),
        "%s|%s|%.2lf",
        transaction.sender,
        transaction.receiver,
        transaction.amount
    );

    cipherLength =
        encryptAES(
            (unsigned char*)plainData,
            strlen(plainData),
            AES_KEY,
            cipherText
        );

    memset(
        transaction.cipherText,
        0,
        sizeof(transaction.cipherText)
    );

    for(int i = 0; i < cipherLength; i++)
    {
        sprintf(
            transaction.cipherText + (i * 2),
            "%02X",
            cipherText[i]
        );
    }

    sha256String(
        plainData,
        transaction.integrityHash
    );

    addTransactionNode(transaction);

    fp = fopen(
        "transactions.txt",
        "a"
    );

    if(fp == NULL)
    {
        printf("Transaction File Error\n");
        return;
    }

    fprintf(
        fp,
        "%d|%s|%s|%.2lf|%s|%s\n",
        transaction.transactionId,
        transaction.sender,
        transaction.receiver,
        transaction.amount,
        transaction.cipherText,
        transaction.integrityHash
    );

    fclose(fp);

    printf(
        "Transaction Created Successfully\n"
    );
}

void displayTransactions(void)
{
    TransactionNode *temp = head;

    if(temp == NULL)
    {
        printf(
            "No Transactions Available\n"
        );
        return;
    }

    printf(
        "\n===== TRANSACTIONS =====\n"
    );

    while(temp != NULL)
    {
        printf(
            "\nTransaction ID : %d\n",
            temp->data.transactionId
        );

        printf(
            "Sender : %s\n",
            temp->data.sender
        );

        printf(
            "Receiver : %s\n",
            temp->data.receiver
        );

        printf(
            "Amount : %.2lf\n",
            temp->data.amount
        );

        temp = temp->next;
    }
}

void verifyIntegrity(void)
{
    TransactionNode *temp = head;

    char transactionData[256];
    char generatedHash[HASH_LENGTH];

    if(temp == NULL)
    {
        printf(
            "No Transactions Available\n"
        );
        return;
    }

    while(temp != NULL)
    {
        snprintf(
            transactionData,
            sizeof(transactionData),
            "%s|%s|%.2lf",
            temp->data.sender,
            temp->data.receiver,
            temp->data.amount
        );

        sha256String(
            transactionData,
            generatedHash
        );

        printf(
            "\nTransaction ID : %d\n",
            temp->data.transactionId
        );

        if(
            strcmp(
                generatedHash,
                temp->data.integrityHash
            ) == 0
        )
        {
            printf(
                "Integrity Verified\n"
            );
        }
        else
        {
            printf(
                "Tampering Detected\n"
            );
        }

        temp = temp->next;
    }
}

void freeTransactionList(void)
{
    TransactionNode *temp;

    while(head != NULL)
    {
        temp = head;

        head = head->next;

        free(temp);
    }
}