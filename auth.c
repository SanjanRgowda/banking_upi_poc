#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "auth.h"
#include "crypto.h"
#include "models.h"

static void generatePasswordHash(
    const char *password,
    const char *salt,
    char hash[HASH_LENGTH]
)
{
    char combined[128];

    snprintf(
        combined,
        sizeof(combined),
        "%s%s",
        salt,
        password
    );

    sha256String(
        combined,
        hash
    );
}

int registerUser(void)
{
    User user;

    FILE *fp;

    char password[50];

    printf("User ID: ");
    scanf("%d", &user.userId);

    printf("Username: ");
    scanf("%49s", user.username);

    printf("Password: ");
    scanf("%49s", password);

    strcpy(user.role, "CUSTOMER");

    generateSalt(user.salt);

    generatePasswordHash(
        password,
        user.salt,
        user.passwordHash
    );

    fp = fopen(
        "users.txt",
        "a"
    );

    if(fp == NULL)
    {
        printf("Unable to open users file\n");
        return 0;
    }

    fprintf(
        fp,
        "%d|%s|%s|%s|%s\n",
        user.userId,
        user.username,
        user.salt,
        user.passwordHash,
        user.role
    );

    fclose(fp);

    printf("User Registered Successfully\n");

    return 1;
}

int loginUser(void)
{
    FILE *fp;

    char username[50];
    char password[50];

    User user;

    char calculatedHash[HASH_LENGTH];

    printf("Username: ");
    scanf("%49s", username);

    printf("Password: ");
    scanf("%49s", password);

    fp = fopen(
        "users.txt",
        "r"
    );

    if(fp == NULL)
    {
        printf("Users Database Missing\n");
        return 0;
    }

    while(
        fscanf(
            fp,
            "%d|%49[^|]|%16[^|]|%64[^|]|%19s\n",
            &user.userId,
            user.username,
            user.salt,
            user.passwordHash,
            user.role
        ) == 5
    )
    {
        if(
            strcmp(
                username,
                user.username
            ) == 0
        )
        {
            generatePasswordHash(
                password,
                user.salt,
                calculatedHash
            );

            if(
                strcmp(
                    calculatedHash,
                    user.passwordHash
                ) == 0
            )
            {
                fclose(fp);

                printf(
                    "Login Successful\n"
                );

                return 1;
            }
        }
    }

    fclose(fp);

    printf(
        "Invalid Credentials\n"
    );

    return 0;
}