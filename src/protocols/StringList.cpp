#include <stdexcept>
#include <protocols/StringList.hpp>

namespace Protocol
{

size_t StringList::fromLengthValueEncodedByteArray(
    const ::ByteArray& bytes,
    size_t offset,
    ::StringList& stringList)
{
    auto totalLength = bytes.size() - offset;
    if (totalLength < 1)
    {
        throw std::invalid_argument("too few bytes in string list");
    }

    stringList.clear();
    size_t index = 0;

    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%02lx", offset);
    while (index < totalLength)
    {
        auto length = bytes.at(offset + index++);
        if (length == 0)
        {
            break;
        }
        // DNS name compression
        else if ((length & 0xc0) == 0xc0)
        {
            if (totalLength < (index + 1))
            {
                throw std::runtime_error("not enough bytes available");
            }

            ::StringList remainingStrings;
            size_t relatedOffset = ((length & 0x3f) << 8) | bytes.at(offset + index++);
            fromLengthValueEncodedByteArray(bytes, relatedOffset, remainingStrings);
            stringList.insert(stringList.end(), remainingStrings.cbegin(), remainingStrings.cend());

            break;
        }

        if (totalLength < (index + length))
        {
            throw std::runtime_error("not enough bytes available");
        }

        stringList.push_back(std::string((const char*) bytes.substr(offset + index, length).c_str(), length));
        index += length;
    }

    return index;
}

::ByteArray StringList::toLengthValueEncodedByteArray(const ::StringList& items)
{
    ::ByteArray bytes;

    for (auto& item: items)
    {
        if (item.size() > 0x3f)
        {
            throw std::domain_error("string too long for length/value encoding");
        }

        bytes += static_cast<uint8_t>(item.size());
        bytes += ::ByteArray((const uint8_t*) item.c_str(), item.size());
    }
    bytes += static_cast<uint8_t>(0);

    return bytes;
}

} /* namespace Protocol */
