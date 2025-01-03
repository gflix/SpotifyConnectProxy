#include <gtest/gtest.h>
#include <models/resource-record-payload/GenericResourceRecordPayload.hpp>

TEST(GenericResourceRecordPayloadTest, checksToString)
{
    // setup
    GenericResourceRecordPayload input { DnsResourceType::NSEC };
    std::string expected { "type=NSEC" };

    // exercise and verify
    EXPECT_EQ(expected, input.toString());
}

TEST(GenericResourceRecordPayloadTest, checksStreamOperator)
{
    // setup
    GenericResourceRecordPayload input { DnsResourceType::NSEC };
    std::string expected { "type=NSEC" };

    // exercise
    std::stringstream actual;
    actual << input;

    // verify
    EXPECT_EQ(expected, actual.str());
}
