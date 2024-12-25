#include <iostream>
#include <controllers/threads/MainThread.hpp>
#include <utils/CommandlineParser.hpp>
#include <utils/Log.hpp>

static void printUsage(
    std::ostream& stream,
    const std::string& programName,
    const CommandlineArguments& defaultArguments)
{
    stream << "USAGE: " << programName << " [OPTIONS] IN OUT..." << std::endl;
    stream << std::endl;
    stream << "Mandatory arguments:" << std::endl;
    stream << "  IN        Interface on which the Spotify Connect device can be reached" << std::endl;
    stream << "  OUT...    One or more interfaces to which the Spotify Connect messages" << std::endl;
    stream << "            shall be proxied" << std::endl;
    stream << std::endl;
    stream << "Optional arguments:" << std::endl;
    stream << "  -l LEVEL  Log level (default: " << defaultArguments.logLevel << ")" << std::endl;
    stream << "  -h        Show this information" << std::endl;
    stream << std::endl;
}

int main(int argc, char const* argv[])
{
    CommandlineArguments commandlineArguments;
    try
    {
        CommandlineParser::parseArguments(argc, argv, commandlineArguments);

        if (commandlineArguments.showHelp)
        {
            printUsage(std::cout, argv[0], CommandlineArguments());
            return 0;
        }

        if (commandlineArguments.inInterface.empty())
        {
            throw std::runtime_error("no IN interface given");
        }
        if (commandlineArguments.outInterfaces.empty())
        {
            throw std::runtime_error("no OUT interface(s) given");
        }
    }
    catch(const std::exception& e)
    {
        LOG_ERROR("Error parsing commandline arguments (" << e.what() << ")! Aborting.");

        printUsage(std::cerr, argv[0], CommandlineArguments());
        return -1;
    }

    Log::instance.setLogLevel(commandlineArguments.logLevel);
    LOG_DEBUG("commandlineArguments=" << commandlineArguments);

    try
    {
        MainThread mainThread { commandlineArguments };

        mainThread.run();
    }
    catch(const std::exception& e)
    {
        LOG_ERROR("MainThread returned an error (" << e.what() << ")! Aborting.");
        return -1;
    }

    return 0;
}
