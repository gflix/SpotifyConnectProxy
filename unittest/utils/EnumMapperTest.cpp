#include <gtest/gtest.h>
#include <utils/EnumMapper.hpp>

enum class TestEnum
{
    A,
    B,
};

const static std::map<TestEnum, std::string> mapping {
    { TestEnum::A, "A" },
    { TestEnum::B, "B" },
};

TEST(EnumMapperTest, checksFromIdentifier)
{
    // setup

    // exercise and verify

    // verify
    EXPECT_EQ(TestEnum::A, EnumMapper<TestEnum>::fromIdentifier(mapping, "A"));
    EXPECT_EQ(TestEnum::B, EnumMapper<TestEnum>::fromIdentifier(mapping, "B"));
    EXPECT_THROW(EnumMapper<TestEnum>::fromIdentifier(mapping, "C"), std::out_of_range);
}

TEST(EnumMapperTest, checksFromIdentifierWithDefault)
{
    // setup

    // exercise and verify

    // verify
    EXPECT_EQ(TestEnum::A, EnumMapper<TestEnum>::fromIdentifierWithDefault(mapping, "A", TestEnum::B));
    EXPECT_EQ(TestEnum::B, EnumMapper<TestEnum>::fromIdentifierWithDefault(mapping, "B", TestEnum::A));
    EXPECT_EQ(TestEnum::B, EnumMapper<TestEnum>::fromIdentifierWithDefault(mapping, "C", TestEnum::B));
}

TEST(EnumMapperTest, checksToIdentifier)
{
    // setup

    // exercise and verify

    // verify
    EXPECT_EQ("A", EnumMapper<TestEnum>::toIdentifier(mapping, TestEnum::A));
    EXPECT_EQ("B", EnumMapper<TestEnum>::toIdentifier(mapping, TestEnum::B));
    EXPECT_THROW(EnumMapper<TestEnum>::toIdentifier(mapping, static_cast<TestEnum>(-1)), std::out_of_range);
}

TEST(EnumMapperTest, checksToIdentifierWithDefault)
{
    // setup

    // exercise and verify

    // verify
    EXPECT_EQ("A", EnumMapper<TestEnum>::toIdentifierWithDefault(mapping, TestEnum::A, "INVALID"));
    EXPECT_EQ("B", EnumMapper<TestEnum>::toIdentifierWithDefault(mapping, TestEnum::B, "INVALID"));
    EXPECT_EQ("INVALID", EnumMapper<TestEnum>::toIdentifierWithDefault(mapping, static_cast<TestEnum>(-1), "INVALID"));
}
