#include <gtest/gtest.h>
#include <models/MdnsResourceRecord.hpp>
#include <models/resource-record-payload/ResourceRecordAPayload.hpp>
#include <protocols/ByteArray.hpp>

TEST(MdnsResourceRecordTest, checksStreamOperator)
{
    // setup
    MdnsResourceRecord input {
        { "host", "example", "com" },
        DnsResourceType::A,
        1,
        true,
        2,
        Protocol::ByteArray::fromHex("0011") };
    std::string expected {
        "MdnsResourceRecord["
            "name=host.example.com,"
            "type=A,"
            "classCode=0001,"
            "cacheFlush=1,"
            "timeToLive=2,"
            "data=00 11"
        "]" };

    // exercise
    std::stringstream actual;
    actual << input;

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(MdnsResourceRecordTest, checksStreamOperatorWithDecodedData)
{
    // setup
    MdnsResourceRecord input {
        { "host", "example", "com" },
        DnsResourceType::A,
        1,
        true,
        2,
        Protocol::ByteArray::fromHex("0011") };
    input.decodedData = std::make_unique<ResourceRecordAPayload>("192.168.0.1");
    std::string expected {
        "MdnsResourceRecord["
            "name=host.example.com,"
            "type=A,"
            "classCode=0001,"
            "cacheFlush=1,"
            "timeToLive=2,"
            "data=00 11,"
            "decodedData=ResourceRecordAPayload[type=A,address=192.168.0.1]"
        "]" };

    // exercise
    std::stringstream actual;
    actual << input;

    // verify
    EXPECT_EQ(expected, actual.str());
}
