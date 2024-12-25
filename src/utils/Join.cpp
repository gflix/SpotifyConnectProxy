#include <utils/Join.hpp>

std::string Join::stringList(const StringList& items, const std::string delimiter)
{
    std::string result;
    bool firstElement = true;

    for (auto& item: items)
    {
        if (firstElement)
        {
            firstElement = false;
        }
        else
        {
            result += delimiter;
        }

        result += item;
    }

    return result;
}
