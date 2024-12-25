#include <unistd.h>
#include <stdexcept>
#include <protocols/LogLevel.hpp>
#include <utils/CommandlineParser.hpp>

void CommandlineParser::parseArguments(int argc, char const* argv[], CommandlineArguments& arguments)
{
    int opt;
    optind = 1;

    while ((opt = getopt(argc, (char**) argv, "l:h")) != -1)
    {
        switch (opt)
        {
            case 'l':
                arguments.logLevel = Protocol::LogLevel::fromIdentifier(optarg);
                break;
            case 'h':
                arguments.showHelp = true;
                break;
            default:
                throw std::invalid_argument("invalid option");
        }
    }

    if (arguments.showHelp)
    {
        return;
    }

    if (optind < argc)
    {
        arguments.inInterface = argv[optind++];
    }

    while (optind < argc)
    {
        std::string interface = argv[optind++];
        if (interface == arguments.inInterface)
        {
            throw std::invalid_argument("OUT interfaces and the IN interface must not be the same");
        }
        arguments.outInterfaces.push_back(interface);
    }
}
