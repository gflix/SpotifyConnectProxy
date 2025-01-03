#include <gtest/gtest.h>
#include <models/resource-record-payload/ResourceRecordAPayload.hpp>

TEST(ResourceRecordAPayloadTest, checksToString)
{
    // setup
    ResourceRecordAPayload input { "192.168.0.1" };
    std::string expected { "ResourceRecordAPayload[type=A,address=192.168.0.1]" };

    // exercise and verify
    EXPECT_EQ(expected, input.toString());
}

TEST(ResourceRecordAPayloadTest, checksStreamOperator)
{
    // setup
    ResourceRecordAPayload input { "192.168.0.1" };
    std::string expected { "ResourceRecordAPayload[type=A,address=192.168.0.1]" };

    // exercise
    std::stringstream actual;
    actual << input;

    // verify
    EXPECT_EQ(expected, actual.str());
}
