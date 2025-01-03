#ifndef MODELS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDSRVPAYLOAD_HPP_
#define MODELS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDSRVPAYLOAD_HPP_

#include <models/StringList.hpp>
#include <models/resource-record-payload/GenericResourceRecordPayload.hpp>

struct ResourceRecordSrvPayload: public GenericResourceRecordPayload
{
    explicit ResourceRecordSrvPayload(
        unsigned int priority = 0,
        unsigned int weight = 0,
        unsigned int port = 0,
        const StringList& target = StringList());
    virtual ~ResourceRecordSrvPayload();

    unsigned int priority;
    unsigned int weight;
    unsigned int port;
    StringList target;

    std::string fullTarget(void) const;
    std::string toString(void) const override;
};

#endif /* MODELS_RESOURCE_RECORD_PAYLOAD_RESOURCERECORDSRVPAYLOAD_HPP_ */
