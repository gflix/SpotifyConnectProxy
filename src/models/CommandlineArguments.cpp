#include <models/CommandlineArguments.hpp>
#include <utils/Containers.hpp>

CommandlineArguments::CommandlineArguments(
    bool showHelp,
    LogLevel logLevel,
    const std::string& inInterface,
    const StringList& outInterfaces):
    showHelp(showHelp),
    logLevel(logLevel),
    inInterface(inInterface),
    outInterfaces(outInterfaces)
{
}

CommandlineArguments::~CommandlineArguments()
{
}

std::ostream& operator<<(std::ostream& stream, const CommandlineArguments& item)
{
    stream << "CommandlineArguments[";
    stream << "showHelp=" << item.showHelp << ",";
    stream << "logLevel=" << item.logLevel << ",";
    stream << "inInterface=" << item.inInterface << ",";
    stream << "outInterfaces=" << item.outInterfaces;
    stream << "]";

    return stream;
}
