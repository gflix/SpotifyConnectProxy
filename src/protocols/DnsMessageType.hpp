#ifndef PROTOCOLS_DNSMESSAGETYPE_HPP_
#define PROTOCOLS_DNSMESSAGETYPE_HPP_

#include <string>
#include <models/DnsMessageType.hpp>

namespace Protocol
{

class DnsMessageType
{
public:
    static std::string toIdentifier(::DnsMessageType item);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_DNSMESSAGETYPE_HPP_ */
