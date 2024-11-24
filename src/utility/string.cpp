#include "utility/string.h"

#include <algorithm>
#include <cctype>
#include <ranges>
#include <regex>
#include <string>
#include <vector>

namespace aoc
{
    std::vector<std::string> split(const std::string& str, const char delim)
    {
        return std::ranges::split_view(str, delim)
            | std::ranges::to<std::vector<std::string>>();
    }

    std::vector<std::string> regex_split(const std::string& str, const std::string& pattern)
    {
        std::regex re(pattern);
        return std::vector<std::string>(
            std::sregex_token_iterator(str.begin(), str.end(), re, -1),
            std::sregex_token_iterator());
    }

    bool is_lower(const std::string& str)
    {
        return std::all_of(str.begin(), str.end(), [](const char c) {return std::islower(c); });
    }

    bool is_upper(const std::string& str)
    {
        return std::all_of(str.begin(), str.end(), [](const char c) { return std::isupper(c); });
    }

    bool is_unique(const std::string& str)
    {
        for (size_t i = 0; i < str.length(); ++i)
        {
            for (size_t j = i + 1; j < str.length(); ++j)
            {
                if (str[i] == str[j])
                {
                    return false;
                }
            }
        }

        return true;
    }

} // aoc
