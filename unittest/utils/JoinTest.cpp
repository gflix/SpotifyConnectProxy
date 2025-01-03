#include <gtest/gtest.h>
#include <utils/Join.hpp>

TEST(JoinTest, joinsStringList)
{
    // setup
    StringList input {
        "foo",
        "bar",
        "baz" };

    std::string expected { "foo,bar,baz" };

    // exercise
    auto actual = Join::stringList(input, ",");

    // verify
    EXPECT_EQ(expected, actual);
}

TEST(JoinTest, joinsStringListWithOtherDelimiter)
{
    // setup
    StringList input {
        "foo",
        "bar",
        "baz" };

    std::string expected { "foo:bar:baz" };

    // exercise
    auto actual = Join::stringList(input, ":");

    // verify
    EXPECT_EQ(expected, actual);
}

TEST(JoinTest, joinsStringListWithoutDelimiter)
{
    // setup
    StringList input {
        "foo",
        "bar",
        "baz" };

    std::string expected { "foobarbaz" };

    // exercise
    auto actual = Join::stringList(input);

    // verify
    EXPECT_EQ(expected, actual);
}
