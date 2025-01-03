#include <gtest/gtest.h>
#include <protocols/LogLevel.hpp>

TEST(LogLevelTest, checksFromIdentifier)
{
    // setup

    // exercise and verify
    EXPECT_EQ(LogLevel::DEBUG, Protocol::LogLevel::fromIdentifier("DEBUG"));
    EXPECT_EQ(LogLevel::INFO, Protocol::LogLevel::fromIdentifier("INFO"));
    EXPECT_EQ(LogLevel::NOTICE, Protocol::LogLevel::fromIdentifier("NOTICE"));
    EXPECT_EQ(LogLevel::WARNING, Protocol::LogLevel::fromIdentifier("WARNING"));
    EXPECT_EQ(LogLevel::ERROR, Protocol::LogLevel::fromIdentifier("ERROR"));
    EXPECT_EQ(LogLevel::DEBUG, Protocol::LogLevel::fromIdentifier("?"));
}

TEST(LogLevelTest, checksToIdentifier)
{
    // setup

    // exercise and verify
    EXPECT_EQ("DEBUG", Protocol::LogLevel::toIdentifier(LogLevel::DEBUG));
    EXPECT_EQ("INFO", Protocol::LogLevel::toIdentifier(LogLevel::INFO));
    EXPECT_EQ("NOTICE", Protocol::LogLevel::toIdentifier(LogLevel::NOTICE));
    EXPECT_EQ("WARNING", Protocol::LogLevel::toIdentifier(LogLevel::WARNING));
    EXPECT_EQ("ERROR", Protocol::LogLevel::toIdentifier(LogLevel::ERROR));
    EXPECT_EQ("UNKNOWN", Protocol::LogLevel::toIdentifier(static_cast<LogLevel>(-1)));
}
