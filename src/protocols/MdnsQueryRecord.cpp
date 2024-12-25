#include <arpa/inet.h>
#include <stdexcept>
#include <protocols/GenericMdnsRecord.hpp>
#include <protocols/MdnsQueryRecord.hpp>
#include <protocols/StringList.hpp>
#include <utils/Conversion.hpp>

namespace Protocol
{

size_t MdnsQueryRecord::fromByteArray(const ::ByteArray& bytes, size_t offset, ::MdnsQueryRecord& record)
{
    auto bytesUsedForGenericRecord = GenericMdnsRecord::fromByteArray(bytes, offset, record);
    if (bytesUsedForGenericRecord < 2)
    {
        throw std::invalid_argument("corrupt bytes for query record");
    }

    record.unicastResponse =
        ntohs(Conversion::uint16FromByteArray(bytes.substr(bytesUsedForGenericRecord + offset - 2, 2))) & 0x8000;

    return bytesUsedForGenericRecord;
}

::ByteArray MdnsQueryRecord::toByteArray(const ::MdnsQueryRecord& item)
{
    ::ByteArray bytes;

    bytes = Protocol::StringList::toLengthValueEncodedByteArray(item.name);
    bytes += Conversion::uint16ToByteArray(htons(static_cast<unsigned int>(item.type)));
    uint16_t flags = 0;
    flags |= (item.unicastResponse ? 0x01 : 0x00) << 15;
    flags |= item.classCode & 0x7fff;
    bytes += Conversion::uint16ToByteArray(htons(flags));

    return bytes;
}

} /* namespace Protocol */
