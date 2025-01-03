#include <stdexcept>
#include <utils/Split.hpp>
#include <utils/Trim.hpp>

StringList Split::string(std::string joinedString, const std::string& separator, bool trim, bool skipEmpty)
{
    if (separator.empty())
    {
        throw std::invalid_argument("empty separator");
    }
    if (joinedString.empty())
    {
        return {};
    }

    StringList strings;
    std::string::size_type position;
    while ((position = joinedString.find(separator)) != std::string::npos)
    {
        std::string element = joinedString.substr(0, position);
        joinedString.erase(0, position + separator.size());

        if (trim)
        {
            element = Trim::both(element);
        }
        if (!element.empty() || !skipEmpty)
        {
            strings.push_back(element);
        }
    }

    if (trim)
    {
        joinedString = Trim::both(joinedString);
    }
    if (!joinedString.empty() || !skipEmpty)
    {
        strings.push_back(joinedString);
    }

    return strings;
}
