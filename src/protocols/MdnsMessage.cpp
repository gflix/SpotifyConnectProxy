#include <arpa/inet.h>
#include <stdexcept>
#include <protocols/MdnsMessage.hpp>
#include <protocols/MdnsQueryRecord.hpp>
#include <protocols/MdnsResourceRecord.hpp>
#include <utils/Conversion.hpp>
#include <utils/Log.hpp>

namespace Protocol
{

::MdnsMessage MdnsMessage::fromByteArray(const ::ByteArray& bytes)
{
    if (bytes.size() < 12)
    {
        throw std::invalid_argument("too few bytes in message");
    }

    ::MdnsMessage message;

    message.transactionId = ntohs(Conversion::uint16FromByteArray(bytes.substr(0, 2)));
    auto flags = ntohs(Conversion::uint16FromByteArray(bytes.substr(2, 2)));
    message.messageType = (flags >> 15) & 0x01 ? DnsMessageType::REPLY : DnsMessageType::QUERY;
    auto opcode = (flags >> 11) & 0x0f;
    if (opcode != 0x00)
    {
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "%02x", opcode);
        throw std::out_of_range("opcode \"0x" + std::string(buffer) + "\" is not supported");
    }
    message.authoritativeAnswer = (flags >> 10) & 0x01;
    message.truncation = (flags >> 9) & 0x01;
    message.recursionDesired = (flags >> 8) & 0x01;
    message.recursionAvailable = (flags >> 7) & 0x01;
    message.responseCode = flags & 0x0f;

    auto queriesCount = ntohs(Conversion::uint16FromByteArray(bytes.substr(4, 2)));
    auto answersCount = ntohs(Conversion::uint16FromByteArray(bytes.substr(6, 2)));
    auto authorityRecordsCount = ntohs(Conversion::uint16FromByteArray(bytes.substr(8, 2)));
    auto aditionalRecordsCount = ntohs(Conversion::uint16FromByteArray(bytes.substr(10, 2)));

    size_t index = 12;
    for (auto i = 0; i < queriesCount; ++i)
    {
        LOG_DEBUG("Query(" << i << ")");
        ::MdnsQueryRecord record;
        auto bytesUsedForRecord = Protocol::MdnsQueryRecord::fromByteArray(bytes, index, record);

        index += bytesUsedForRecord;
        message.questions.push_back(record);
    }
    for (auto i = 0; i < answersCount; ++i)
    {
        LOG_DEBUG("Answer(" << i << ")");
        ::MdnsResourceRecord record;
        auto bytesUsedForRecord = Protocol::MdnsResourceRecord::fromByteArray(bytes, index, record);

        index += bytesUsedForRecord;
        message.answers.push_back(std::move(record));
    }
    for (auto i = 0; i < authorityRecordsCount; ++i)
    {
        LOG_DEBUG("Authority(" << i << ")");
        ::MdnsResourceRecord record;
        auto bytesUsedForRecord = Protocol::MdnsResourceRecord::fromByteArray(bytes, index, record);

        index += bytesUsedForRecord;
        message.authorityRecords.push_back(std::move(record));
    }
    for (auto i = 0; i < aditionalRecordsCount; ++i)
    {
        LOG_DEBUG("Additional(" << i << ")");
        ::MdnsResourceRecord record;
        auto bytesUsedForRecord = Protocol::MdnsResourceRecord::fromByteArray(bytes, index, record);

        index += bytesUsedForRecord;
        message.additionalRecords.push_back(std::move(record));
    }

    return message;
}

::ByteArray MdnsMessage::toByteArray(const ::MdnsMessage& item)
{
    ::ByteArray bytes;

    bytes += Conversion::uint16ToByteArray(htons(item.transactionId));
    uint16_t flags = 0;
    flags |= ((item.messageType == DnsMessageType::REPLY) ? 0x01 : 0x00) << 15;
    flags |= (item.authoritativeAnswer ? 0x01 : 0x00) << 10;
    flags |= (item.truncation ? 0x01 : 0x00) << 9;
    flags |= (item.recursionDesired ? 0x01 : 0x00) << 8;
    flags |= (item.recursionAvailable ? 0x01 : 0x00) << 7;
    flags |= item.responseCode & 0x0f;
    bytes += Conversion::uint16ToByteArray(htons(flags));
    bytes += Conversion::uint16ToByteArray(htons(item.questions.size()));
    bytes += Conversion::uint16ToByteArray(htons(item.answers.size()));
    bytes += Conversion::uint16ToByteArray(htons(item.authorityRecords.size()));
    bytes += Conversion::uint16ToByteArray(htons(item.additionalRecords.size()));

    for (auto& record: item.questions)
    {
        bytes += MdnsQueryRecord::toByteArray(record);
    }
    for (auto& record: item.answers)
    {
        bytes += MdnsResourceRecord::toByteArray(record);
    }

    return bytes;
}

} /* namespace Protocol */
