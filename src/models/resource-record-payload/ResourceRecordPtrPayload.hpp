#ifndef MODELS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDPTRPAYLOAD_HPP_
#define MODELS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDPTRPAYLOAD_HPP_

#include <models/StringList.hpp>
#include <models/resource-record-payload/GenericResourceRecordPayload.hpp>

struct ResourceRecordPtrPayload: public GenericResourceRecordPayload
{
    explicit ResourceRecordPtrPayload(
        DnsResourceType type,
        const StringList& domainName = StringList());
    virtual ~ResourceRecordPtrPayload();

    StringList domainName;

    std::string fullDomainName(void) const;
    std::string toString(void) const override;
};

#endif /* MODELS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDPTRPAYLOAD_HPP_ */
