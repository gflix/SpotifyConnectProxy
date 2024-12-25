#include <models/MdnsQueryRecord.hpp>

MdnsQueryRecord::MdnsQueryRecord(
    StringList name,
    DnsResourceType type,
    unsigned int classCode,
    bool unicastResponse):
    GenericMdnsRecord(name, type, classCode),
    unicastResponse(unicastResponse)
{
}

MdnsQueryRecord::~MdnsQueryRecord()
{
}

std::ostream& operator<<(std::ostream& stream, const MdnsQueryRecord& item)
{
    stream << "MdnsQueryRecord[";
    stream << item.toString() << ",";
    stream << "unicastResponse=" << item.unicastResponse;
    stream << "]";

    return stream;
}
