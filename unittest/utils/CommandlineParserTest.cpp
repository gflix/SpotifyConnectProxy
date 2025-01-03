#include <gtest/gtest.h>
#include <utils/CommandlineParser.hpp>

TEST(CommandlineParserTest, checksParseArgumentsWithoutArguments)
{
    // setup
    int argc = 1;
    const char* argv[] = {
        "programName"
    };
    CommandlineArguments commandlineArguments;
    std::string expected {
        "CommandlineArguments["
            "showHelp=0,"
            "logLevel=NOTICE,"
            "inInterface=,"
            "outInterfaces=()"
        "]" };

    // exercise
    ASSERT_NO_THROW(CommandlineParser::parseArguments(argc, argv, commandlineArguments));
    std::stringstream actual;
    actual << commandlineArguments;

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(CommandlineParserTest, checksParseArgumentsWithHelpArgument)
{
    // setup
    int argc = 2;
    const char* argv[] = {
        "programName",
        "-h"
    };
    CommandlineArguments commandlineArguments;
    std::string expected {
        "CommandlineArguments["
            "showHelp=1,"
            "logLevel=NOTICE,"
            "inInterface=,"
            "outInterfaces=()"
        "]" };

    // exercise
    ASSERT_NO_THROW(CommandlineParser::parseArguments(argc, argv, commandlineArguments));
    std::stringstream actual;
    actual << commandlineArguments;

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(CommandlineParserTest, checksParseArgumentsWithArgumentsI)
{
    // setup
    int argc = 6;
    const char* argv[] = {
        "programName",
        "-l",
        "INFO",
        "eth0",
        "eth1",
        "eth2"
    };
    CommandlineArguments commandlineArguments;
    std::string expected {
        "CommandlineArguments["
            "showHelp=0,"
            "logLevel=INFO,"
            "inInterface=eth0,"
            "outInterfaces=(eth1,eth2)"
        "]" };

    // exercise
    ASSERT_NO_THROW(CommandlineParser::parseArguments(argc, argv, commandlineArguments));
    std::stringstream actual;
    actual << commandlineArguments;

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(CommandlineParserTest, checksParseArgumentsWithArgumentsII)
{
    // setup
    int argc = 6;
    const char* argv[] = {
        "programName",
        "-l",
        "INFO",
        "eth0",
        "  eth1  eth2 ",
        "eth3"
    };
    CommandlineArguments commandlineArguments;
    std::string expected {
        "CommandlineArguments["
            "showHelp=0,"
            "logLevel=INFO,"
            "inInterface=eth0,"
            "outInterfaces=(eth1,eth2,eth3)"
        "]" };

    // exercise
    ASSERT_NO_THROW(CommandlineParser::parseArguments(argc, argv, commandlineArguments));
    std::stringstream actual;
    actual << commandlineArguments;

    // verify
    EXPECT_EQ(expected, actual.str());
}

TEST(CommandlineParserTest, throwsWhenParsingArgumentsWithUnknownArgument)
{
    // setup
    int argc = 2;
    const char* argv[] = {
        "programName",
        "-q"
    };
    CommandlineArguments commandlineArguments;

    // exercise and verify
    EXPECT_THROW(CommandlineParser::parseArguments(argc, argv, commandlineArguments), std::invalid_argument);
}

TEST(CommandlineParserTest, throwsWhenParsingArgumentsWithOutInterfaceIsInInterface)
{
    // setup
    int argc = 4;
    const char* argv[] = {
        "programName",
        "eth0",
        "eth1",
        "eth0"
    };
    CommandlineArguments commandlineArguments;

    // exercise and verify
    EXPECT_THROW(CommandlineParser::parseArguments(argc, argv, commandlineArguments), std::invalid_argument);
}
