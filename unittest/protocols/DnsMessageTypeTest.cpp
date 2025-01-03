#include <gtest/gtest.h>
#include <protocols/DnsMessageType.hpp>

TEST(DnsMessageTypeTest, checksToIdentifier)
{
    // setup

    // exercise and verify
    EXPECT_EQ("QUERY", Protocol::DnsMessageType::toIdentifier(DnsMessageType::QUERY));
    EXPECT_EQ("REPLY", Protocol::DnsMessageType::toIdentifier(DnsMessageType::REPLY));
    EXPECT_EQ("INVALID", Protocol::DnsMessageType::toIdentifier(static_cast<DnsMessageType>(-1)));
}
