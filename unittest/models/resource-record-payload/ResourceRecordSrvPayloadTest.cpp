#include <gtest/gtest.h>
#include <models/resource-record-payload/ResourceRecordSrvPayload.hpp>

TEST(ResourceRecordSrvPayloadTest, checksToString)
{
    // setup
    ResourceRecordSrvPayload input { 3, 100, 4711, { "device", "local" } };
    std::string expected { "ResourceRecordSrvPayload[type=SRV,priority=3,weight=100,port=4711,target=device.local]" };

    // exercise and verify
    EXPECT_EQ(expected, input.toString());
}

TEST(ResourceRecordSrvPayloadTest, checksStreamOperator)
{
    // setup
    ResourceRecordSrvPayload input { 3, 100, 4711, { "device", "local" } };
    std::string expected { "ResourceRecordSrvPayload[type=SRV,priority=3,weight=100,port=4711,target=device.local]" };

    // exercise
    std::stringstream actual;
    actual << input;

    // verify
    EXPECT_EQ(expected, actual.str());
}
