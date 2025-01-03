#include <gtest/gtest.h>
#include <models/DnsMessageType.hpp>

TEST(DnsMessageTypeTest, checksStreamOperator)
{
    // setup
    std::string expected { "QUERY" };

    // exercise
    std::stringstream actual;
    actual << DnsMessageType::QUERY;

    // verify
    EXPECT_EQ(expected, actual.str());
}
