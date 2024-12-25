#ifndef MODELS_DNSMESSAGETYPE_HPP_
#define MODELS_DNSMESSAGETYPE_HPP_

#include <ostream>

enum class DnsMessageType
{
    QUERY = 0,
    REPLY = 1,
    INVALID = -1,
};

std::ostream& operator<<(std::ostream& stream, const DnsMessageType& item);

#endif /* MODELS_DNSMESSAGETYPE_HPP_ */
