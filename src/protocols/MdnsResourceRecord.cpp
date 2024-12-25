#include <arpa/inet.h>
#include <stdexcept>
#include <protocols/GenericMdnsRecord.hpp>
#include <protocols/MdnsResourceRecord.hpp>
#include <protocols/StringList.hpp>
#include <protocols/resource-record-payload/GenericResourceRecordPayload.hpp>
#include <utils/Conversion.hpp>

namespace Protocol
{

size_t MdnsResourceRecord::fromByteArray(const ::ByteArray& bytes, size_t offset, ::MdnsResourceRecord& record)
{
    auto bytesUsedForGenericRecord = GenericMdnsRecord::fromByteArray(bytes, offset, record);
    if (bytesUsedForGenericRecord < 2)
    {
        throw std::invalid_argument("corrupt bytes for query record");
    }

    if (bytes.size() - offset < bytesUsedForGenericRecord + 6)
    {
        throw std::invalid_argument("too few bytes in record after generic part");
    }

    record.cacheFlush =
        ntohs(Conversion::uint16FromByteArray(bytes.substr(bytesUsedForGenericRecord + offset - 2, 2))) & 0x8000;
    record.timeToLive =
        ntohl(Conversion::uint32FromByteArray(bytes.substr(bytesUsedForGenericRecord + offset, 4)));

    auto dataLength = ntohs(Conversion::uint16FromByteArray(bytes.substr(bytesUsedForGenericRecord + offset + 4, 2)));

    if (bytes.size() - offset - 6 < dataLength)
    {
        throw std::invalid_argument("too few bytes in record for data");
    }

    record.data = bytes.substr(bytesUsedForGenericRecord + offset + 6, dataLength);

    record.decodedData.reset(
        GenericResourceRecordPayload::fromByteArray(
            bytes,
            bytesUsedForGenericRecord + offset + 6,
            dataLength,
            record.type));

    return bytesUsedForGenericRecord + 6 + dataLength;
}

::ByteArray MdnsResourceRecord::toByteArray(const ::MdnsResourceRecord& item)
{
    ::ByteArray bytes;

    bytes = Protocol::StringList::toLengthValueEncodedByteArray(item.name);
    bytes += Conversion::uint16ToByteArray(htons(static_cast<unsigned int>(item.type)));
    uint16_t flags = 0;
    flags |= (item.cacheFlush ? 0x01 : 0x00) << 15;
    flags |= item.classCode & 0x7fff;
    bytes += Conversion::uint16ToByteArray(htons(flags));
    bytes += Conversion::uint32ToByteArray(htonl(item.timeToLive));
    bytes += Conversion::uint16ToByteArray(htons(item.data.size()));
    bytes += item.data;

    return bytes;
}

} /* namespace Protocol */
