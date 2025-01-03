#include <gtest/gtest.h>
#include <models/CommandlineArguments.hpp>

TEST(CommandlineArgumentsTest, checksStreamOperator)
{
    // setup
    auto input = CommandlineArguments(true, LogLevel::INFO, "eth0", { "eth1", "eth2" });

    std::string expected { };

    // exercise
    std::stringstream actual;
    actual << input;

    // verify
    EXPECT_EQ(expected, actual.str());
}
