#include <gtest/gtest.h>
#include <protocols/resource-record-payload/ResourceRecordAPayload.hpp>
#include <protocols/ByteArray.hpp>

TEST(ResourceRecordAPayloadTest, checksFromByteArray)
{
    // setup
    auto input = Protocol::ByteArray::fromHex("00000a0c0002");
    std::string expected { "ResourceRecordAPayload[type=A,address=10.12.0.2]" };

    // exercise
    std::stringstream actual;
    actual << Protocol::ResourceRecordAPayload::fromByteArray(input, 2);

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(ResourceRecordAPayloadTest, throwsWhenConvertingFromByteArrayWithTooFewBytes)
{
    // setup
    auto input = Protocol::ByteArray::fromHex("00000a0c00");

    // exercise and verify
    EXPECT_THROW(Protocol::ResourceRecordAPayload::fromByteArray(input, 2), std::runtime_error);
}

TEST(ResourceRecordAPayloadTest, checksToByteArray)
{
    // setup
    ResourceRecordAPayload input { "10.192.0.64" };
    std::string expected { "0a c0 00 40" };

    // exercise
    std::stringstream actual;
    actual << Protocol::ByteArray::toHex(Protocol::ResourceRecordAPayload::toByteArray(input), " ");

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(ResourceRecordAPayloadTest, throwsWhenConvertingToByteArrayWithInvalidIpAddress)
{
    // setup
    ResourceRecordAPayload input { "256.192.0.64" };

    // exercise and verify
    EXPECT_THROW(Protocol::ResourceRecordAPayload::toByteArray(input), std::runtime_error);
}
