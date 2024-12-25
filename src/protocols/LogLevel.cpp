#include <protocols/LogLevel.hpp>
#include <utils/EnumMapper.hpp>

namespace Protocol
{

const static std::map<std::string, ::LogLevel> mapping {
    { "ERROR", ::LogLevel::ERROR },
    { "WARNING", ::LogLevel::WARNING },
    { "NOTICE", ::LogLevel::NOTICE },
    { "INFO", ::LogLevel::INFO },
    { "DEBUG", ::LogLevel::DEBUG },
};

::LogLevel LogLevel::fromIdentifier(const std::string& identifier)
{
    return ::EnumMapper<::LogLevel>::fromIdentifierWithDefault(
        mapping,
        identifier,
        ::LogLevel::DEBUG);
}

std::string LogLevel::toIdentifier(::LogLevel logLevel)
{
    return ::EnumMapper<::LogLevel>::toIdentifierWithDefault(mapping, logLevel, "DEBUG");
}

} /* namespace Protocol */
