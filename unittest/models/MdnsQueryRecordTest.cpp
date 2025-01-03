#include <gtest/gtest.h>
#include <models/MdnsQueryRecord.hpp>
#include <protocols/ByteArray.hpp>

TEST(MdnsQueryRecordTest, checksStreamOperator)
{
    // setup
    MdnsQueryRecord input { { "host", "example", "com" }, DnsResourceType::A, 1, true };
    std::string expected { "MdnsQueryRecord[name=host.example.com,type=A,classCode=0001,unicastResponse=1]" };

    // exercise
    std::stringstream actual;
    actual << input;

    // verify
    EXPECT_EQ(expected, actual.str());
}
