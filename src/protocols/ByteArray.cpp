#include <stdexcept>
#include <protocols/ByteArray.hpp>

namespace Protocol
{

uint8_t ByteArray::decodeHexDigit(char digit)
{
    if (digit >= '0' && digit <= '9')
    {
        return digit - '0';
    }
    else if (digit >= 'a' && digit <= 'f')
    {
        return digit + 10 - 'a';
    }
    else if (digit >= 'A' && digit <= 'F')
    {
        return digit + 10 - 'A';
    }
    throw std::invalid_argument("invalid hex digit");
}

::ByteArray ByteArray::fromHex(const std::string& input)
{
    if (input.size() & 1)
    {
        throw std::invalid_argument("require even number of characters when decoding hex string to ByteArray");
    }

    auto it = input.cbegin();
    ::ByteArray byteArray;
    while (it != input.cend())
    {
        uint8_t value = decodeHexDigit(*it) << 4;
        ++it;
        value |= decodeHexDigit(*it);
        ++it;

        byteArray.push_back(value);
    }

    return byteArray;
}

std::string ByteArray::toHex(const ::ByteArray& data, const std::string& separator, bool upperCase)
{
    std::string hex;
    char buffer[4];
    bool firstValue = true;
    const char* formatString = upperCase ? "%02X" : "%02x";

    for (auto& value: data)
    {
        snprintf(buffer, sizeof(buffer), formatString, value);

        if (firstValue)
        {
            hex = buffer;
            firstValue = false;
        }
        else
        {
            hex += separator + std::string(buffer);
        }
    }

    return hex;
}

} /* namespace Protocol */
