#include <protocols/StringList.hpp>
#include <protocols/resource-record-payload/ResourceRecordPtrPayload.hpp>

namespace Protocol
{

::ResourceRecordPtrPayload ResourceRecordPtrPayload::fromByteArray(
    const ::ByteArray& bytes,
    size_t offset)
{
    ::ResourceRecordPtrPayload result;
    Protocol::StringList::fromLengthValueEncodedByteArray(bytes, offset, result.domainName);

    return result;
}

::ByteArray ResourceRecordPtrPayload::toByteArray(const ::ResourceRecordPtrPayload& item)
{
    ::ByteArray bytes;

    bytes = Protocol::StringList::toLengthValueEncodedByteArray(item.domainName);

    return bytes;
}

} /* namespace Protocol */
