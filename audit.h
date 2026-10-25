#ifndef AUDIT_H
#define AUDIT_H

void writeAuditLog(
    const char *event
);

void viewAuditLogs(void);

#endif