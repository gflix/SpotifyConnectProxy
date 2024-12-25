#ifndef UTILS_COMMANDLINEPARSER_HPP_
#define UTILS_COMMANDLINEPARSER_HPP_

#include <models/CommandlineArguments.hpp>

class CommandlineParser
{
public:
    static void parseArguments(int argc, char const* argv[], CommandlineArguments& arguments);
};

#endif /* UTILS_COMMANDLINEPARSER_HPP_ */
