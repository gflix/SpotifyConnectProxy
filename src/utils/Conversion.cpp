#include <stdexcept>
#include <utils/Conversion.hpp>

uint16_t Conversion::uint16FromByteArray(const ::ByteArray& bytes)
{
    if (bytes.size() != 2)
    {
        throw std::domain_error("invalid byte count for uint16 conversion");
    }

    return *((const uint16_t*) bytes.data());
}

uint32_t Conversion::uint32FromByteArray(const ::ByteArray& bytes)
{
    if (bytes.size() != 4)
    {
        throw std::domain_error("invalid byte count for uint32 conversion");
    }

    return *((const uint32_t*) bytes.data());
}

::ByteArray Conversion::uint16ToByteArray(uint16_t value)
{
    return ::ByteArray((const uint8_t*) &value, 2);
}

::ByteArray Conversion::uint32ToByteArray(uint32_t value)
{
    return ::ByteArray((const uint8_t*) &value, 4);
}
