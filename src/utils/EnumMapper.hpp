#ifndef UTILS_ENUMMAPPER_HPP_
#define UTILS_ENUMMAPPER_HPP_

#include <map>
#include <stdexcept>
#include <string>

/// @brief Templated conversion helper methods to convert between string identifiers and enumeration with the use of
///        a map
template<typename T>
class EnumMapper
{
public:
    /// @brief Converts a string identifier to an enumeration value with the use of a map and throw if not found
    static T fromIdentifier(const std::map<std::string, T>& mapping, const std::string& identifier)
    {
        auto value = mapping.find(identifier);
        if (value == mapping.cend())
        {
            throw std::out_of_range("\"" + identifier + "\" is an invalid identifier");
        }
        return value->second;
    }

    /// @brief Converts a string identifier to an enumeration value with the use of a map and
    ///        return a default if not found
    static T fromIdentifierWithDefault(
        const std::map<std::string, T>& mapping,
        const std::string& identifier,T defaultValue)
    {
        try
        {
            return fromIdentifier(mapping, identifier);
        }
        catch (std::out_of_range&)
        {
            return defaultValue;
        }
    }

    /// @brief Converts an enumeration value to a string identifier with the use of a map and throw if not found
    static const std::string& toIdentifier(
        const std::map<std::string, T>& mapping,
        T value)
    {
        std::string identifier;
        auto entry = mapping.cbegin();
        for (; entry != mapping.cend(); ++entry)
        {
            if (entry->second == value)
            {
                return entry->first;
            }
        }

        throw std::out_of_range("no identifier for given enum value found");
    }

    /// @brief Converts an enumeration value to a string identifier with the use of a map and
    ///        return a default if not found
    static const std::string& toIdentifierWithDefault(
        const std::map<std::string, T>& mapping,
        T value,
        const std::string& defaultIdentifier)
    {
        try
        {
            return toIdentifier(mapping, value);
        }
        catch (std::out_of_range&)
        {
            return defaultIdentifier;
        }
    }
};

#endif /* UTILS_ENUMMAPPER_HPP_ */
