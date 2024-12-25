#include <models/MdnsResourceRecord.hpp>
#include <protocols/ByteArray.hpp>

MdnsResourceRecord::MdnsResourceRecord(
    StringList name,
    DnsResourceType type,
    unsigned int classCode,
    bool cacheFlush,
    unsigned int timeToLive,
    ByteArray data):
    GenericMdnsRecord(name, type, classCode),
    cacheFlush(cacheFlush),
    timeToLive(timeToLive),
    data(data)
{
}

MdnsResourceRecord::~MdnsResourceRecord()
{
}

std::ostream& operator<<(std::ostream& stream, const MdnsResourceRecord& item)
{
    stream << "MdnsResourceRecord[";
    stream << item.toString() << ",";
    stream << "cacheFlush=" << item.cacheFlush << ",";
    stream << "timeToLive=" << item.timeToLive << ",";
    stream << "data=" << Protocol::ByteArray::toHex(item.data, " ");
    if (item.decodedData)
    {
        stream << ",decodedData=" << *item.decodedData;
    }
    stream << "]";

    return stream;
}
