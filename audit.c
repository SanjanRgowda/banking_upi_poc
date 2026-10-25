#include <stdio.h>
#include <time.h>

#include "audit.h"

void writeAuditLog(
    const char *event
)
{
    FILE *fp;

    time_t currentTime;

    char *timeString;

    fp = fopen(
        "audit_log.txt",
        "a"
    );

    if(fp == NULL)
    {
        printf(
            "Unable to Open Audit Log File\n"
        );
        return;
    }

    currentTime = time(NULL);

    timeString = ctime(&currentTime);

    fprintf(
        fp,
        "[%s] %s\n",
        timeString,
        event
    );

    fclose(fp);
}

void viewAuditLogs(void)
{
    FILE *fp;

    char line[512];

    fp = fopen(
        "audit_log.txt",
        "r"
    );

    if(fp == NULL)
    {
        printf(
            "No Audit Logs Available\n"
        );
        return;
    }

    printf(
        "\n===== AUDIT LOGS =====\n"
    );

    while(
        fgets(
            line,
            sizeof(line),
            fp
        ) != NULL
    )
    {
        printf(
            "%s",
            line
        );
    }

    fclose(fp);
}