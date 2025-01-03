#include <gtest/gtest.h>
#include <models/IpProtocol.hpp>

TEST(IpProtocolTest, checksStreamOperator)
{
    // setup
    std::string expected { "IPV6" };

    // exercise
    std::stringstream actual;
    actual << IpProtocol::IPV6;

    // verify
    EXPECT_EQ(expected, actual.str());
}
