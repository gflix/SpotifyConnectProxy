#include <arpa/inet.h>
#include <stdexcept>
#include <protocols/DnsResourceType.hpp>
#include <protocols/GenericMdnsRecord.hpp>
#include <protocols/StringList.hpp>
#include <utils/Conversion.hpp>

namespace Protocol
{

size_t GenericMdnsRecord::fromByteArray(const ::ByteArray& bytes, size_t offset, ::GenericMdnsRecord& record)
{
    if (bytes.size() - offset < 5)
    {
        throw std::invalid_argument("too few bytes in record");
    }

    auto bytesUsedForNames = StringList::fromLengthValueEncodedByteArray(bytes, offset, record.name);
    if (bytes.size() - offset < (bytesUsedForNames + 4))
    {
        throw std::invalid_argument("too few bytes in record after name");
    }

    record.type = DnsResourceType::fromInteger(
        ntohs(Conversion::uint16FromByteArray(bytes.substr(bytesUsedForNames + offset, 2))));
    record.classCode =
        ntohs(Conversion::uint16FromByteArray(bytes.substr(bytesUsedForNames + offset + 2, 2))) & 0x7fff;

    return bytesUsedForNames + 4;
}

} /* namespace Protocol */
