#ifndef PROTOCOLS_IPPROTOCOL_HPP_
#define PROTOCOLS_IPPROTOCOL_HPP_

#include <string>
#include <models/IpProtocol.hpp>

namespace Protocol
{

class IpProtocol
{
public:
    static std::string toIdentifier(::IpProtocol item);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_IPPROTOCOL_HPP_ */
