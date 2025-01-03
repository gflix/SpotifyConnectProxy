#include <protocols/IpProtocol.hpp>
#include <utils/EnumMapper.hpp>

namespace Protocol
{

const static std::map<::IpProtocol, std::string> mapping {
    { ::IpProtocol::IPV4, "IPV4" },
    { ::IpProtocol::IPV6, "IPV6" },
};


std::string IpProtocol::toIdentifier(::IpProtocol item)
{
    return EnumMapper<::IpProtocol>::toIdentifierWithDefault(mapping, item, "INVALID");
}

} /* namespace Protocol */
