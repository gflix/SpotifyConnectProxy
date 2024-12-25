#ifndef MODELS_MDNSMESSAGE_HPP_
#define MODELS_MDNSMESSAGE_HPP_

#include <ostream>
#include <models/DnsMessageType.hpp>
#include <models/MdnsQueryRecord.hpp>
#include <models/MdnsResourceRecord.hpp>

struct MdnsMessage
{
    explicit MdnsMessage(
        unsigned int transactionId = 0,
        DnsMessageType messageType = DnsMessageType::INVALID,
        bool authoritativeAnswer = false,
        bool truncation = false,
        bool recursionDesired = false,
        bool recursionAvailable = false,
        unsigned int responseCode = 0,
        const MdnsQueryRecords& questions = MdnsQueryRecords(),
        MdnsResourceRecords&& answers = MdnsResourceRecords(),
        MdnsResourceRecords&& authorityRecords = MdnsResourceRecords(),
        MdnsResourceRecords&& additionalRecords = MdnsResourceRecords());
    MdnsMessage(MdnsMessage&&) = default;
    virtual ~MdnsMessage();

    unsigned int transactionId;
    DnsMessageType messageType;
    bool authoritativeAnswer;
    bool truncation;
    bool recursionDesired;
    bool recursionAvailable;
    unsigned int responseCode;

    MdnsQueryRecords questions;
    MdnsResourceRecords answers;
    MdnsResourceRecords authorityRecords;
    MdnsResourceRecords additionalRecords;

    bool hasResourceRecords(void) const;
    bool hasAnswers(void) const;
    bool hasAuthorityRecords(void) const;
    bool hasAdditionalRecords(void) const;

    static MdnsMessage query(
        MdnsQueryRecords questions = MdnsQueryRecords(),
        unsigned int transactionId = 0);
    static MdnsMessage reply(
        bool authoritativeAnswer = true,
        unsigned int transactionId = 0);
};

std::ostream& operator<<(std::ostream& stream, const MdnsMessage& item);

#endif /* MODELS_MDNSMESSAGE_HPP_ */
