#include <gtest/gtest.h>
#include <utils/Containers.hpp>
#include <utils/Split.hpp>

TEST(SplitTest, splitsString)
{
    // setup
    std::string input { "foo: bar::baz " };

    std::string expected { "(foo, bar,baz )" };

    // exercise
    std::stringstream actual;
    actual << Split::string(input, ":");

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(SplitTest, splitsEmptyString)
{
    // setup
    std::string input { };

    std::string expected { "()" };

    // exercise
    std::stringstream actual;
    actual << Split::string(input, ":");

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(SplitTest, throwsWhenSplittingStringWithoutSeparator)
{
    // setup
    std::string input { "foo:bar" };

    // exercise and verify
    EXPECT_THROW(Split::string(input, std::string()), std::invalid_argument);
}

TEST(SplitTest, splitsStringWithTrim)
{
    // setup
    std::string input { "foo: bar::baz " };

    std::string expected { "(foo,bar,baz)" };

    // exercise
    std::stringstream actual;
    actual << Split::string(input, ":", true);

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(SplitTest, splitsStringWithoutSkippingEmptyEntries)
{
    // setup
    std::string input { "foo: bar::baz " };

    std::string expected { "(foo, bar,,baz )" };

    // exercise
    std::stringstream actual;
    actual << Split::string(input, ":", false, false);

    // verify
    EXPECT_EQ(expected, actual.str());
}
