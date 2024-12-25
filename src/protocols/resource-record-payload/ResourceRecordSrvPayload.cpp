#include <netinet/ip.h>
#include <protocols/StringList.hpp>
#include <protocols/resource-record-payload/ResourceRecordSrvPayload.hpp>
#include <utils/Conversion.hpp>

namespace Protocol
{

::ResourceRecordSrvPayload ResourceRecordSrvPayload::fromByteArray(
    const ::ByteArray& bytes,
    size_t offset,
    DnsResourceType type)
{
    if (bytes.size() - offset < 7)
    {
        throw std::invalid_argument("insufficient bytes for SRV record");
    }

    ::ResourceRecordSrvPayload result {
        type,
        ntohs(Conversion::uint16FromByteArray(bytes.substr(offset, 2))),
        ntohs(Conversion::uint16FromByteArray(bytes.substr(offset + 2, 2))),
        ntohs(Conversion::uint16FromByteArray(bytes.substr(offset + 4, 2))) };

    Protocol::StringList::fromLengthValueEncodedByteArray(bytes, offset + 6, result.target);

    return result;
}

::ByteArray ResourceRecordSrvPayload::toByteArray(const ::ResourceRecordSrvPayload& item)
{
    ::ByteArray bytes;

    bytes += Conversion::uint16ToByteArray(htons(static_cast<unsigned int>(item.priority)));
    bytes += Conversion::uint16ToByteArray(htons(static_cast<unsigned int>(item.weight)));
    bytes += Conversion::uint16ToByteArray(htons(static_cast<unsigned int>(item.port)));
    bytes += Protocol::StringList::toLengthValueEncodedByteArray(item.target);

    return bytes;
}

} /* namespace Protocol */
