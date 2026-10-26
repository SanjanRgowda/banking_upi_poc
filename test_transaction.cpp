#include <gtest/gtest.h>

extern "C"
{
#include "crypto.h"
}

TEST(TransactionTest, IntegrityHashLength)
{
    char hash[65];

    sha256String(
        "Alice|Bob|1000",
        hash
    );

    EXPECT_EQ(
        strlen(hash),
        64
    );
}

TEST(TransactionTest, IntegrityChangesWhenDataChanges)
{
    char hash1[65];
    char hash2[65];

    sha256String(
        "Alice|Bob|1000",
        hash1
    );

    sha256String(
        "Alice|Bob|5000",
        hash2
    );

    EXPECT_STRNE(
        hash1,
        hash2
    );
}