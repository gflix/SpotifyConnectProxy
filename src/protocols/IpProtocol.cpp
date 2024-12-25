#include <protocols/IpProtocol.hpp>
#include <utils/EnumMapper.hpp>

namespace Protocol
{

const static std::map<std::string, ::IpProtocol> mapping {
    { "IPV4", ::IpProtocol::IPV4 },
    { "IPV6", ::IpProtocol::IPV6 },
};


std::string IpProtocol::toIdentifier(::IpProtocol item)
{
    return EnumMapper<::IpProtocol>::toIdentifierWithDefault(mapping, item, "INVALID");
}

} /* namespace Protocol */
