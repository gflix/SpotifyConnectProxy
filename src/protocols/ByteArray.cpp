#include <protocols/ByteArray.hpp>

namespace Protocol
{

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
