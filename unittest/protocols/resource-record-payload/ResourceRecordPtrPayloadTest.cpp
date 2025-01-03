#include <gtest/gtest.h>
#include <protocols/resource-record-payload/ResourceRecordPtrPayload.hpp>
#include <protocols/ByteArray.hpp>

TEST(ResourceRecordPtrPayloadTest, checksFromByteArray)
{
    // setup
    auto input = Protocol::ByteArray::fromHex("0000014103434f4d00");
    std::string expected { "ResourceRecordPtrPayload[type=PTR,domainName=A.COM]" };

    // exercise
    std::stringstream actual;
    actual << Protocol::ResourceRecordPtrPayload::fromByteArray(input, 2);

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(ResourceRecordPtrPayloadTest, checksToByteArray)
{
    // setup
    ResourceRecordPtrPayload input { { "dev", "local" } };
    std::string expected { "03 64 65 76 05 6c 6f 63 61 6c 00" };

    // exercise
    std::stringstream actual;
    actual << Protocol::ByteArray::toHex(Protocol::ResourceRecordPtrPayload::toByteArray(input), " ");

    // verify
    EXPECT_EQ(expected, actual.str());
}
