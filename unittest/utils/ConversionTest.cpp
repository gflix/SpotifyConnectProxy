#include <gtest/gtest.h>
#include <protocols/ByteArray.hpp>
#include <utils/Conversion.hpp>

TEST(ConversionTest, convertsUint16FromByteArray)
{
    // setup
    ByteArray input;
    input.push_back(0x12);
    input.push_back(0x34);

    uint16_t expected = 0x3412u;

    // exercise
    auto actual = Conversion::uint16FromByteArray(input);

    // verify
    EXPECT_EQ(expected, actual);
}

TEST(ConversionTest, throwsWhenConvertingUint16FromByteArrayWithInvalidLength)
{
    // setup
    ByteArray input;
    input.push_back(0x12);

    // exercise and verify
    EXPECT_THROW(Conversion::uint16FromByteArray(input), std::domain_error);
}

TEST(ConversionTest, convertsUint32FromByteArray)
{
    // setup
    ByteArray input;
    input.push_back(0x12);
    input.push_back(0x34);
    input.push_back(0x56);
    input.push_back(0x78);

    uint32_t expected = 0x78563412u;

    // exercise
    auto actual = Conversion::uint32FromByteArray(input);

    // verify
    EXPECT_EQ(expected, actual);
}

TEST(ConversionTest, throwsWhenConvertingUint32FromByteArrayWithInvalidLength)
{
    // setup
    ByteArray input;
    input.push_back(0x12);
    input.push_back(0x34);
    input.push_back(0x56);

    // exercise and verify
    EXPECT_THROW(Conversion::uint32FromByteArray(input), std::domain_error);
}

TEST(ConversionTest, convertsUint16ToByteArray)
{
    // setup
    uint16_t input = 0xfedcu;

    std::string expected { "dc fe" };

    // exercise
    auto actual = Protocol::ByteArray::toHex(Conversion::uint16ToByteArray(input), " ");

    // verify
    EXPECT_EQ(expected, actual);
}

TEST(ConversionTest, convertsUint32ToByteArray)
{
    // setup
    uint32_t input = 0xfedcba98u;

    std::string expected { "98 ba dc fe" };

    // exercise
    auto actual = Protocol::ByteArray::toHex(Conversion::uint32ToByteArray(input), " ");

    // verify
    EXPECT_EQ(expected, actual);
}
