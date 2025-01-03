#include <gtest/gtest.h>
#include <models/LogLevel.hpp>

TEST(LogLevelTest, checksStreamOperator)
{
    // setup
    std::string expected { "NOTICE" };

    // exercise
    std::stringstream actual;
    actual << LogLevel::NOTICE;

    // verify
    EXPECT_EQ(expected, actual.str());
}
