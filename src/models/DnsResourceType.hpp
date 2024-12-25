#ifndef MODELS_DNSRESOURCETYPE_HPP_
#define MODELS_DNSRESOURCETYPE_HPP_

#include <ostream>

enum class DnsResourceType
{
    A = 1,
    PTR = 12,
    TXT = 16,
    AAAA = 28,
    SRV = 33,
    NSEC = 47,
    ANY = 255,
    INVALID = -1,
};

std::ostream& operator<<(std::ostream& stream, const DnsResourceType& item);

#endif /* MODELS_DNSRESOURCETYPE_HPP_ */
