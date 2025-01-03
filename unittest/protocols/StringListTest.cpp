#include <gtest/gtest.h>
#include <protocols/ByteArray.hpp>
#include <protocols/StringList.hpp>
#include <utils/Containers.hpp>

TEST(StringListTest, checksFromLengthValueEncodedByteArrayTrivial)
{
    // setup
    auto input = Protocol::ByteArray::fromHex("03464f4f0642415242415200");
    std::string expected { "(FOO,BARBAR)" };

    // exercise
    std::stringstream actual;
    StringList stringList;
    ASSERT_NO_THROW(Protocol::StringList::fromLengthValueEncodedByteArray(input, 0, stringList));
    actual << stringList;

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(StringListTest, checksFromLengthValueEncodedByteArrayWithOffset)
{
    // setup
    auto input = Protocol::ByteArray::fromHex("03464f4f0642415242415200");
    std::string expected { "(BARBAR)" };

    // exercise
    std::stringstream actual;
    StringList stringList;
    ASSERT_NO_THROW(Protocol::StringList::fromLengthValueEncodedByteArray(input, 4, stringList));
    actual << stringList;

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(StringListTest, checksFromLengthValueEncodedByteArrayWithMultipleStringLists)
{
    // setup
    auto input = Protocol::ByteArray::fromHex("03464f4f0642415242415200014100");
    std::string expectedA { "(FOO,BARBAR)" };
    std::string expectedB { "(A)" };

    // exercise
    std::stringstream actualA;
    StringList stringList;
    ASSERT_NO_THROW(Protocol::StringList::fromLengthValueEncodedByteArray(input, 0, stringList));
    actualA << stringList;

    std::stringstream actualB;
    ASSERT_NO_THROW(Protocol::StringList::fromLengthValueEncodedByteArray(input, 12, stringList));
    actualB << stringList;

    // verify
    EXPECT_EQ(expectedA, actualA.str());
    EXPECT_EQ(expectedB, actualB.str());
}

TEST(StringListTest, checksFromLengthValueEncodedByteArrayWithDnsNameCompression)
{
    // setup
    auto input = Protocol::ByteArray::fromHex("03464f4f06424152424152000141c00400");
    std::string expectedA { "(FOO,BARBAR)" };
    std::string expectedB { "(A,BARBAR)" };

    // exercise
    std::stringstream actualA;
    StringList stringList;
    ASSERT_NO_THROW(Protocol::StringList::fromLengthValueEncodedByteArray(input, 0, stringList));
    actualA << stringList;

    std::stringstream actualB;
    ASSERT_NO_THROW(Protocol::StringList::fromLengthValueEncodedByteArray(input, 12, stringList));
    actualB << stringList;

    // verify
    EXPECT_EQ(expectedA, actualA.str());
    EXPECT_EQ(expectedB, actualB.str());
}

TEST(StringListTest, throwsWhenConvertingFromLengthValueEncodedByteArrayWithTooFewBytes)
{
    // setup
    auto input = Protocol::ByteArray::fromHex("013000");
    StringList stringList;

    // exercise and verify
    EXPECT_THROW(Protocol::StringList::fromLengthValueEncodedByteArray(input, 3, stringList), std::invalid_argument);
}

TEST(StringListTest, throwsWhenConvertingFromLengthValueEncodedByteArrayWithMissingLengthByteInDnsNameCompression)
{
    // setup
    auto input = Protocol::ByteArray::fromHex("013000c0");
    StringList stringList;

    // exercise and verify
    EXPECT_THROW(Protocol::StringList::fromLengthValueEncodedByteArray(input, 3, stringList), std::runtime_error);
}

TEST(StringListTest, throwsWhenConvertingFromLengthValueEncodedByteArrayWithTooFewDataBytes)
{
    // setup
    auto input = Protocol::ByteArray::fromHex("033000");
    StringList stringList;

    // exercise and verify
    EXPECT_THROW(Protocol::StringList::fromLengthValueEncodedByteArray(input, 0, stringList), std::runtime_error);
}

TEST(StringListTest, checksToLengthValueEncodedByteArray)
{
    // setup
    StringList input { "foo", "barbar" };
    std::string expected { "03 66 6f 6f 06 62 61 72 62 61 72 00" };

    // exercise
    auto actual = Protocol::ByteArray::toHex(Protocol::StringList::toLengthValueEncodedByteArray(input), " ");

    // verify
    EXPECT_EQ(expected, actual);
}

TEST(StringListTest, throwsWhenConvertingToLengthValueEncodedByteArrayWithTooLongInput)
{
    // setup
    StringList input { "0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef" };

    // exercise and verify
    EXPECT_THROW(Protocol::StringList::toLengthValueEncodedByteArray(input), std::domain_error);
}
