#ifndef PROTOCOLS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDPTRPAYLOAD_HPP_
#define PROTOCOLS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDPTRPAYLOAD_HPP_

#include <models/ByteArray.hpp>
#include <models/resource-record-payload/ResourceRecordPtrPayload.hpp>

namespace Protocol
{

class ResourceRecordPtrPayload
{
public:
    static ::ResourceRecordPtrPayload fromByteArray(
        const ::ByteArray& bytes,
        size_t offset,
        DnsResourceType type);
    static ::ByteArray toByteArray(const ::ResourceRecordPtrPayload& item);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDPTRPAYLOAD_HPP_ */
