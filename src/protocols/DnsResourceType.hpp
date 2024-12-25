#ifndef PROTOCOLS_DNSRESOURCETYPE_HPP_
#define PROTOCOLS_DNSRESOURCETYPE_HPP_

#include <string>
#include <models/DnsResourceType.hpp>

namespace Protocol
{

class DnsResourceType
{
public:
    static std::string toIdentifier(::DnsResourceType item);
    static ::DnsResourceType fromInteger(unsigned int value);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_DNSRESOURCETYPE_HPP_ */
