#include <gtest/gtest.h>
#include <protocols/ByteArray.hpp>

TEST(ByteArrayTest, convertsFromHex)
{
    // setup
    ByteArray expected { 0x01, 0x89, 0xab, 0xef };

    // exercise
    auto actual = Protocol::ByteArray::fromHex("0189abEF");

    // verify
    EXPECT_EQ(expected, actual);
}

TEST(ByteArrayTest, throwsWhenConvertingFromHexWithOddInput)
{
    // setup

    // exercise and verify
    EXPECT_THROW(Protocol::ByteArray::fromHex("0189abE"), std::invalid_argument);
}

TEST(ByteArrayTest, throwsWhenConvertingFromHexWithInvalidInput)
{
    // setup

    // exercise and verify
    EXPECT_THROW(Protocol::ByteArray::fromHex("0189abE?"), std::invalid_argument);
}

TEST(ByteArrayTest, checksToHex)
{
    // setup
    ByteArray input;
    input.push_back(0x00);
    input.push_back(0xff);
    input.push_back(0x12);
    input.push_back(0xcd);

    std::string expected { "00ff12cd" };

    // exercise
    auto actual = Protocol::ByteArray::toHex(input);

    // verify
    EXPECT_EQ(expected, actual);
}

TEST(ByteArrayTest, checksToHexWithDelimiter)
{
    // setup
    ByteArray input;
    input.push_back(0x00);
    input.push_back(0xff);
    input.push_back(0x12);
    input.push_back(0xcd);

    std::string expected { "00:ff:12:cd" };

    // exercise
    auto actual = Protocol::ByteArray::toHex(input, ":");

    // verify
    EXPECT_EQ(expected, actual);
}

TEST(ByteArrayTest, checksToHexUppercas)
{
    // setup
    ByteArray input;
    input.push_back(0x00);
    input.push_back(0xff);
    input.push_back(0x12);
    input.push_back(0xcd);

    std::string expected { "00:FF:12:CD" };

    // exercise
    auto actual = Protocol::ByteArray::toHex(input, ":", true);

    // verify
    EXPECT_EQ(expected, actual);
}
