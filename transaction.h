#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "models.h"

extern TransactionNode *head;

void createTransaction(void);
void displayTransactions(void);
void verifyIntegrity(void);
void freeTransactionList(void);
void loadTransactionsFromFile(void);

#endif
