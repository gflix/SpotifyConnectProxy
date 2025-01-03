#include <gtest/gtest.h>
#include <protocols/IpProtocol.hpp>

TEST(IpProtocolTest, checksToIdentifier)
{
    // setup

    // exercise and verify
    EXPECT_EQ("IPV4", Protocol::IpProtocol::toIdentifier(IpProtocol::IPV4));
    EXPECT_EQ("IPV6", Protocol::IpProtocol::toIdentifier(IpProtocol::IPV6));
    EXPECT_EQ("INVALID", Protocol::IpProtocol::toIdentifier(static_cast<IpProtocol>(-1)));
}
