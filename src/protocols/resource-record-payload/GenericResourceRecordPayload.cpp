#include <protocols/resource-record-payload/GenericResourceRecordPayload.hpp>
#include <protocols/resource-record-payload/ResourceRecordAPayload.hpp>
#include <protocols/resource-record-payload/ResourceRecordPtrPayload.hpp>
#include <protocols/resource-record-payload/ResourceRecordSrvPayload.hpp>
#include <protocols/resource-record-payload/ResourceRecordTxtPayload.hpp>

namespace Protocol
{

::GenericResourceRecordPayload* GenericResourceRecordPayload::fromByteArray(
    const ::ByteArray& bytes,
    size_t offset,
    ssize_t length,
    DnsResourceType type)
{
    switch (type)
    {
        case DnsResourceType::A:
            return new ::ResourceRecordAPayload(ResourceRecordAPayload::fromByteArray(bytes, offset, type));
        case DnsResourceType::PTR:
            return new ::ResourceRecordPtrPayload(ResourceRecordPtrPayload::fromByteArray(bytes, offset, type));
        case DnsResourceType::SRV:
            return new ::ResourceRecordSrvPayload(ResourceRecordSrvPayload::fromByteArray(bytes, offset, type));
        case DnsResourceType::TXT:
            return new ::ResourceRecordTxtPayload(ResourceRecordTxtPayload::fromByteArray(bytes, offset, length, type));
        default:
            return nullptr;
    }
}

} /* namespace Protocol */
