#include <protocols/LogLevel.hpp>
#include <utils/EnumMapper.hpp>

namespace Protocol
{

const static std::map<::LogLevel, std::string> mapping {
    { ::LogLevel::ERROR, "ERROR" },
    { ::LogLevel::WARNING, "WARNING" },
    { ::LogLevel::NOTICE, "NOTICE" },
    { ::LogLevel::INFO, "INFO" },
    { ::LogLevel::DEBUG, "DEBUG" },
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
    return ::EnumMapper<::LogLevel>::toIdentifierWithDefault(mapping, logLevel, "UNKNOWN");
}

} /* namespace Protocol */
