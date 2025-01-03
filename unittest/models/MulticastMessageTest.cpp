#include <gtest/gtest.h>
#include <models/MulticastMessage.hpp>
#include <protocols/ByteArray.hpp>

TEST(MulticastMessageTest, checksStreamOperator)
{
    // setup
    MulticastMessage input { Protocol::ByteArray::fromHex("012345"), "192.168.0.1", 1234, IpProtocol::IPV4 };
    std::string expected { "MulticastMessage[message=01 23 45,host=192.168.0.1,port=1234,protocol=IPV4]" };

    // exercise
    std::stringstream actual;
    actual << input;

    // verify
    EXPECT_EQ(expected, actual.str());
}
