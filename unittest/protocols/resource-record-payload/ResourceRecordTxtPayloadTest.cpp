#include <gtest/gtest.h>
#include <protocols/resource-record-payload/ResourceRecordTxtPayload.hpp>
#include <protocols/ByteArray.hpp>

TEST(ResourceRecordTxtPayloadTest, checksFromByteArray)
{
    // setup
    auto input = Protocol::ByteArray::fromHex("0000014103434f4d");
    std::string expected { "ResourceRecordTxtPayload[type=TXT,lines=(A,COM)]" };

    // exercise
    std::stringstream actual;
    actual << Protocol::ResourceRecordTxtPayload::fromByteArray(input, 2, 6);

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(ResourceRecordTxtPayloadTest, checksToByteArray)
{
    // setup
    ResourceRecordTxtPayload input { { "dev", "local" } };
    std::string expected { "03 64 65 76 05 6c 6f 63 61 6c" };

    // exercise
    std::stringstream actual;
    actual << Protocol::ByteArray::toHex(Protocol::ResourceRecordTxtPayload::toByteArray(input), " ");

    // verify
    EXPECT_EQ(expected, actual.str());
}
