#include <gtest/gtest.h>
#include <fstream>

extern "C"
{
#include "audit.h"
}

TEST(AuditTest, AuditFileCreated)
{
    writeAuditLog(
        "TEST EVENT"
    );

    std::ifstream file(
        "audit_log.txt"
    );

    EXPECT_TRUE(
        file.good()
    );

    file.close();
}