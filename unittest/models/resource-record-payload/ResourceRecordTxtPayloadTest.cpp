#include <gtest/gtest.h>
#include <models/resource-record-payload/ResourceRecordTxtPayload.hpp>

TEST(ResourceRecordTxtPayloadTest, checksToString)
{
    // setup
    ResourceRecordTxtPayload input { { "A", "B" } };
    std::string expected { "ResourceRecordTxtPayload[type=TXT,lines=(A,B)]" };

    // exercise and verify
    EXPECT_EQ(expected, input.toString());
}

TEST(ResourceRecordTxtPayloadTest, checksStreamOperator)
{
    // setup
    ResourceRecordTxtPayload input { { "A", "B" } };
    std::string expected { "ResourceRecordTxtPayload[type=TXT,lines=(A,B)]" };

    // exercise
    std::stringstream actual;
    actual << input;

    // verify
    EXPECT_EQ(expected, actual.str());
}
