#include <gtest/gtest.h>
#include <protocols/resource-record-payload/ResourceRecordSrvPayload.hpp>
#include <protocols/ByteArray.hpp>

TEST(ResourceRecordSrvPayloadTest, checksFromByteArray)
{
    // setup
    auto input = Protocol::ByteArray::fromHex("0000123456789abc0141");
    std::string expected { "ResourceRecordSrvPayload[type=SRV,priority=4660,weight=22136,port=39612,target=A]" };

    // exercise
    std::stringstream actual;
    actual << Protocol::ResourceRecordSrvPayload::fromByteArray(input, 2);

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(ResourceRecordSrvPayloadTest, throwsWhenConvertingFromByteArrayWithTooFewBytes)
{
    // setup
    auto input = Protocol::ByteArray::fromHex("0000123456789abc");

    // exercise and verify
    EXPECT_THROW(Protocol::ResourceRecordSrvPayload::fromByteArray(input, 2), std::invalid_argument);
}

TEST(ResourceRecordSrvPayloadTest, checksToByteArray)
{
    // setup
    ResourceRecordSrvPayload input { 32, 4096, 16384, { "host", "local" } };
    std::string expected { "00 20 10 00 40 00 04 68 6f 73 74 05 6c 6f 63 61 6c 00" };

    // exercise
    std::stringstream actual;
    actual << Protocol::ByteArray::toHex(Protocol::ResourceRecordSrvPayload::toByteArray(input), " ");

    // verify
    EXPECT_EQ(expected, actual.str());
}
