#ifndef PROTOCOLS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDSRVPAYLOAD_HPP_
#define PROTOCOLS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDSRVPAYLOAD_HPP_

#include <models/ByteArray.hpp>
#include <models/resource-record-payload/ResourceRecordSrvPayload.hpp>

namespace Protocol
{

class ResourceRecordSrvPayload
{
public:
    static ::ResourceRecordSrvPayload fromByteArray(
        const ::ByteArray& bytes,
        size_t offset);
    static ::ByteArray toByteArray(const ::ResourceRecordSrvPayload& item);
};

} /* namespace Protocol */

#endif /* PROTOCOLS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDSRVPAYLOAD_HPP_ */
