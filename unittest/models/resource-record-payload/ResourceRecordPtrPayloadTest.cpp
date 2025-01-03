#include <gtest/gtest.h>
#include <models/resource-record-payload/ResourceRecordPtrPayload.hpp>

TEST(ResourceRecordPtrPayloadTest, checksToString)
{
    // setup
    ResourceRecordPtrPayload input { { "host", "example", "com" } };
    std::string expected { "ResourceRecordPtrPayload[type=PTR,domainName=host.example.com]" };

    // exercise and verify
    EXPECT_EQ(expected, input.toString());
}

TEST(ResourceRecordPtrPayloadTest, checksStreamOperator)
{
    // setup
    ResourceRecordPtrPayload input { { "host", "example", "com" } };
    std::string expected { "ResourceRecordPtrPayload[type=PTR,domainName=host.example.com]" };

    // exercise
    std::stringstream actual;
    actual << input;

    // verify
    EXPECT_EQ(expected, actual.str());
}
