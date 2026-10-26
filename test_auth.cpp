#include <gtest/gtest.h>

extern "C"
{
#include "crypto.h"
}

TEST(AuthTest, PasswordHashConsistency)
{
    char hash1[65];
    char hash2[65];

    sha256String(
        "Password123",
        hash1
    );

    sha256String(
        "Password123",
        hash2
    );

    EXPECT_STREQ(
        hash1,
        hash2
    );
}

TEST(AuthTest, DifferentPasswordsDifferentHashes)
{
    char hash1[65];
    char hash2[65];

    sha256String(
        "Password123",
        hash1
    );

    sha256String(
        "Password456",
        hash2
    );

    EXPECT_STRNE(
        hash1,
        hash2
    );
}