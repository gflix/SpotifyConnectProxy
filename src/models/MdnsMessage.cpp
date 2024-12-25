#include <models/MdnsMessage.hpp>
#include <utils/Containers.hpp>

MdnsMessage::MdnsMessage(
    unsigned int transactionId,
    DnsMessageType messageType,
    bool authoritativeAnswer,
    bool truncation,
    bool recursionDesired,
    bool recursionAvailable,
    unsigned int responseCode,
    const MdnsQueryRecords& questions,
    MdnsResourceRecords&& answers,
    MdnsResourceRecords&& authorityRecords,
    MdnsResourceRecords&& additionalRecords):
    transactionId(transactionId),
    messageType(messageType),
    authoritativeAnswer(authoritativeAnswer),
    truncation(truncation),
    recursionDesired(recursionDesired),
    recursionAvailable(recursionAvailable),
    responseCode(responseCode),
    questions(questions),
    answers(std::move(answers)),
    authorityRecords(std::move(authorityRecords)),
    additionalRecords(std::move(additionalRecords))
{
}

MdnsMessage::~MdnsMessage()
{
}

bool MdnsMessage::hasResourceRecords(void) const
{
    return
        hasAnswers() ||
        hasAuthorityRecords() ||
        hasAdditionalRecords();
}

bool MdnsMessage::hasAnswers(void) const
{
    return !answers.empty();
}

bool MdnsMessage::hasAuthorityRecords(void) const
{
    return !authorityRecords.empty();
}

bool MdnsMessage::hasAdditionalRecords(void) const
{
    return !additionalRecords.empty();
}

MdnsMessage MdnsMessage::query(
    MdnsQueryRecords questions,
    unsigned int transactionId)
{
    return MdnsMessage(transactionId, DnsMessageType::QUERY, false, false, false, false, 0, questions);
}

MdnsMessage MdnsMessage::reply(
    bool authoritativeAnswer,
    unsigned int transactionId)
{
    return MdnsMessage(
        transactionId,
        DnsMessageType::REPLY,
        authoritativeAnswer);
}

std::ostream& operator<<(std::ostream& stream, const MdnsMessage& item)
{
    char buffer[16];

    stream << "MdnsMessage[";
    snprintf(buffer, sizeof(buffer), "%04x", item.transactionId);
    stream << "transactionId=" << buffer << ",";
    stream << "messageType=" << item.messageType << ",";
    stream << "authoritativeAnswer=" << item.authoritativeAnswer << ",";
    stream << "truncation=" << item.truncation << ",";
    stream << "recursionDesired=" << item.recursionDesired << ",";
    stream << "recursionAvailable=" << item.recursionAvailable << ",";
    stream << "responseCode=" << item.responseCode << ",";
    stream << "questions=" << item.questions << ",";
    stream << "answers=" << item.answers << ",";
    stream << "authorityRecords=" << item.authorityRecords << ",";
    stream << "additionalRecords=" << item.additionalRecords;
    stream << "]";

    return stream;
}