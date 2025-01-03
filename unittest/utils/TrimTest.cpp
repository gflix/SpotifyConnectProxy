#include <gtest/gtest.h>
#include <utils/Trim.hpp>

TEST(TrimTest, checksLeft)
{
    // setup
    std::string inputA { "ABC" };
    std::string inputB { "ABC \r\n" };
    std::string inputC { "\n\r ABC \r\n" };
    std::string expectedC { "ABC \r\n" };
    std::string inputD { "\n\r A\nB\rC D \r\n" };
    std::string expectedD { "A\nB\rC D \r\n" };
    std::string inputE { "\n\r  \r\n" };
    std::string expectedE { };

    // exercise and verify
    EXPECT_EQ(Trim::left(inputA), inputA);
    EXPECT_EQ(Trim::left(inputB), inputB);
    EXPECT_EQ(Trim::left(inputC), expectedC);
    EXPECT_EQ(Trim::left(inputD), expectedD);
    EXPECT_EQ(Trim::left(inputE), expectedE);
}

TEST(TrimTest, checksRight)
{
    // setup
    std::string inputA { "ABC" };
    std::string inputB { " \r\nABC" };
    std::string inputC { "\n\r ABC \r\n" };
    std::string expectedC { "\n\r ABC" };
    std::string inputD { "\n\r A\nB\rC D \r\n" };
    std::string expectedD { "\n\r A\nB\rC D" };
    std::string inputE { "\n\r  \r\n" };
    std::string expectedE { };

    // exercise and verify
    EXPECT_EQ(Trim::right(inputA), inputA);
    EXPECT_EQ(Trim::right(inputB), inputB);
    EXPECT_EQ(Trim::right(inputC), expectedC);
    EXPECT_EQ(Trim::right(inputD), expectedD);
    EXPECT_EQ(Trim::right(inputE), expectedE);
}

TEST(TrimTest, checksBoth)
{
    // setup
    std::string inputA { "ABC" };
    std::string inputB { "\n\r A\nB\rC D \r\n" };
    std::string expectedB { "A\nB\rC D" };

    // exercise and verify
    EXPECT_EQ(Trim::both(inputA), inputA);
    EXPECT_EQ(Trim::both(inputB), expectedB);
}
