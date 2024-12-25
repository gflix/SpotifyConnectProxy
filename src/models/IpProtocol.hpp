#ifndef MODELS_IPPROTOCOL_HPP_
#define MODELS_IPPROTOCOL_HPP_

#include <ostream>

enum class IpProtocol
{
    IPV4,
    IPV6,
    INVALID,
};

std::ostream& operator<<(std::ostream& stream, const IpProtocol& item);

#endif /* MODELS_IPPROTOCOL_HPP_ */
