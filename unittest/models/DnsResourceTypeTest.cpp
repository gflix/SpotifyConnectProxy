#include <gtest/gtest.h>
#include <models/DnsResourceType.hpp>

TEST(DnsResourceTypeTest, checksStreamOperator)
{
    // setup
    std::string expected { "AAAA" };

    // exercise
    std::stringstream actual;
    actual << DnsResourceType::AAAA;

    // verify
    EXPECT_EQ(expected, actual.str());
}
