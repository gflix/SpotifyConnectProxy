#include <arpa/inet.h>
#include <stdexcept>
#include <protocols/resource-record-payload/ResourceRecordAPayload.hpp>
#include <utils/Conversion.hpp>

namespace Protocol
{

::ResourceRecordAPayload ResourceRecordAPayload::fromByteArray(
    const ::ByteArray& bytes,
    size_t offset,
    DnsResourceType type)
{
    ::ResourceRecordAPayload result {
        type };

    if (bytes.size() - offset < 4)
    {
        throw std::runtime_error("insufficient bytes for IPv4 address");
    }
    in_addr ipAddress;
    char ipAddressBuffer[INET_ADDRSTRLEN];
    ipAddress.s_addr = Conversion::uint32FromByteArray(bytes.substr(offset, 4));
    inet_ntop(AF_INET, &ipAddress, ipAddressBuffer, INET_ADDRSTRLEN);

    result.address = ipAddressBuffer;

    return result;
}

::ByteArray ResourceRecordAPayload::toByteArray(const ::ResourceRecordAPayload& item)
{
    ::ByteArray bytes;

    in_addr ipAddress;
    if (inet_pton(AF_INET, item.address.c_str(), &ipAddress.s_addr) != 1)
    {
        throw std::runtime_error("invalid IPv4 address \"" + item.address + "\"");
    }

    bytes += Conversion::uint32ToByteArray(ipAddress.s_addr);

    return bytes;
}

} /* namespace Protocol */
