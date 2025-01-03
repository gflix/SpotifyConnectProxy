#include <gtest/gtest.h>
#include <protocols/DnsResourceType.hpp>

TEST(DnsResourceTypeTest, checksToIdentifier)
{
    // setup

    // exercise and verify
    EXPECT_EQ("A", Protocol::DnsResourceType::toIdentifier(DnsResourceType::A));
    EXPECT_EQ("AAAA", Protocol::DnsResourceType::toIdentifier(DnsResourceType::AAAA));
    EXPECT_EQ("ANY", Protocol::DnsResourceType::toIdentifier(DnsResourceType::ANY));
    EXPECT_EQ("NSEC", Protocol::DnsResourceType::toIdentifier(DnsResourceType::NSEC));
    EXPECT_EQ("PTR", Protocol::DnsResourceType::toIdentifier(DnsResourceType::PTR));
    EXPECT_EQ("SRV", Protocol::DnsResourceType::toIdentifier(DnsResourceType::SRV));
    EXPECT_EQ("TXT", Protocol::DnsResourceType::toIdentifier(DnsResourceType::TXT));
    EXPECT_EQ("INVALID", Protocol::DnsResourceType::toIdentifier(static_cast<DnsResourceType>(-1)));
}

TEST(DnsResourceTypeTest, checksFromInteger)
{
    // setup

    // exercise and verify
    EXPECT_EQ(DnsResourceType::A, Protocol::DnsResourceType::fromInteger(1));
    EXPECT_EQ(DnsResourceType::AAAA, Protocol::DnsResourceType::fromInteger(28));
    EXPECT_EQ(DnsResourceType::ANY, Protocol::DnsResourceType::fromInteger(255));
    EXPECT_EQ(DnsResourceType::NSEC, Protocol::DnsResourceType::fromInteger(47));
    EXPECT_EQ(DnsResourceType::PTR, Protocol::DnsResourceType::fromInteger(12));
    EXPECT_EQ(DnsResourceType::SRV, Protocol::DnsResourceType::fromInteger(33));
    EXPECT_EQ(DnsResourceType::TXT, Protocol::DnsResourceType::fromInteger(16));
    EXPECT_THROW(Protocol::DnsResourceType::fromInteger(0), std::out_of_range);
}
