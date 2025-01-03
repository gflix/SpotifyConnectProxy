#include <gtest/gtest.h>
#include <utils/Containers.hpp>

TEST(ContainersTest, streamsVector)
{
    // setup
    std::vector<std::string> input { "foo", "bar", "baz" };

    std::string expected { "(foo,bar,baz)" };

    // exercise
    std::stringstream actual;
    actual << input;

    // verify
    EXPECT_EQ(expected, actual.str());
}
