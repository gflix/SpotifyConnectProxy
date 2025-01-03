#include <utils/Trim.hpp>

std::string Trim::left(const std::string& text)
{
    std::string::size_type position = text.find_first_not_of(" \n\r");
    if (position == std::string::npos)
    {
        return std::string();
    }

    return
        text.substr(position);
}

std::string Trim::right(const std::string& text)
{
    std::string::size_type position = text.find_last_not_of(" \n\r");
    if (position == std::string::npos)
    {
        return std::string();
    }

    return
        text.substr(0, position + 1);
}

std::string Trim::both(const std::string& text)
{
    return
        left(right(text));
}
