#ifndef PROTOCOLS_LOGLEVEL_HPP_
#define PROTOCOLS_LOGLEVEL_HPP_

#include <string>
#include <models/LogLevel.hpp>

namespace Protocol
{

class LogLevel
{
public:
    static ::LogLevel fromIdentifier(const std::string& identifier);
    static std::string toIdentifier(::LogLevel logLevel);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_LOGLEVEL_HPP_ */
