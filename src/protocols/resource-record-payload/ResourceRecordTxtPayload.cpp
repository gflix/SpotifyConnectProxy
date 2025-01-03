#include <protocols/StringList.hpp>
#include <protocols/resource-record-payload/ResourceRecordTxtPayload.hpp>

namespace Protocol
{

::ResourceRecordTxtPayload ResourceRecordTxtPayload::fromByteArray(
    const ::ByteArray& bytes,
    size_t offset,
    ssize_t length)
{
    ::ResourceRecordTxtPayload result;
    Protocol::StringList::fromLengthValueEncodedByteArray(bytes.substr(offset, length), 0, result.lines);

    return result;
}

::ByteArray ResourceRecordTxtPayload::toByteArray(const ::ResourceRecordTxtPayload& item)
{
    ::ByteArray bytes;

    bytes = Protocol::StringList::toLengthValueEncodedByteArray(item.lines);
    bytes.erase(bytes.size() - 1); // remove trailing 0-byte

    return bytes;
}

} /* namespace Protocol */
