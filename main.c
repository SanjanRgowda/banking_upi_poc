#include <stdio.h>

#include "auth.h"
#include "transaction.h"
#include "audit.h"

int main(void)
{
    int choice;
    int loggedIn = 0;

    do
    {
        printf("\n");
        printf("===========================================\n");
        printf(" DIGITAL BANKING & UPI SECURITY PLATFORM\n");
        printf("===========================================\n");

        printf("1. Register User\n");
        printf("2. Login\n");
        printf("3. Create Transaction\n");
        printf("4. Display Transactions\n");
        printf("5. Verify Transaction Integrity\n");
        printf("6. View Audit Logs\n");
        printf("7. Exit\n");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:

                if(registerUser())
                {
                    writeAuditLog(
                        "USER REGISTERED"
                    );
                }

                break;

            case 2:

                loggedIn = loginUser();

                if(loggedIn)
                {
                    writeAuditLog(
                        "LOGIN SUCCESS"
                    );
                }
                else
                {
                    writeAuditLog(
                        "LOGIN FAILURE"
                    );
                }

                break;

            case 3:

                if(loggedIn)
                {
                    createTransaction();

                    writeAuditLog(
                        "TRANSACTION CREATED"
                    );
                }
                else
                {
                    printf(
                        "Please Login First\n"
                    );
                }

                break;

            case 4:

                if(loggedIn)
                {
                    displayTransactions();
                }
                else
                {
                    printf(
                        "Please Login First\n"
                    );
                }

                break;

            case 5:

                if(loggedIn)
                {
                    verifyIntegrity();

                    writeAuditLog(
                        "INTEGRITY VERIFICATION PERFORMED"
                    );
                }
                else
                {
                    printf(
                        "Please Login First\n"
                    );
                }

                break;

            case 6:

                viewAuditLogs();

                break;

            case 7:

                writeAuditLog(
                    "SYSTEM EXIT"
                );

                printf(
                    "Exiting Application...\n"
                );

                break;

            default:

                printf(
                    "Invalid Choice\n"
                );
        }

    } while(choice != 7);

    freeTransactionList();

    return 0;
}