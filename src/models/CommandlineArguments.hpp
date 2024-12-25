#ifndef MODELS_COMMANDLINEARGUMENTS_HPP_
#define MODELS_COMMANDLINEARGUMENTS_HPP_

#include <ostream>
#include <models/LogLevel.hpp>
#include <models/StringList.hpp>

struct CommandlineArguments
{
    explicit CommandlineArguments(
        bool showHelp = false,
        LogLevel logLevel = LogLevel::NOTICE,
        const std::string& inInterface = std::string(),
        const StringList& outInterfaces = StringList());
    virtual ~CommandlineArguments();

    bool showHelp;
    LogLevel logLevel;
    std::string inInterface;
    StringList outInterfaces;
};

std::ostream& operator<<(std::ostream& stream, const CommandlineArguments& item);

#endif /* MODELS_COMMANDLINEARGUMENTS_HPP_ */
