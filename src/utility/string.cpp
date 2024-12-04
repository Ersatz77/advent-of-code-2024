#include "utility/string.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <ranges>
#include <string>
#include <vector>

namespace aoc
{
    std::vector<std::string> split(const std::string_view str, const std::string_view delim)
    {
        return std::views::split(str, delim) | std::ranges::to<std::vector<std::string>>();
    }

    bool is_lower(const std::string_view str)
    {
        return std::all_of(str.begin(), str.end(), std::islower);
    }

    bool is_upper(const std::string_view str)
    {
        return std::all_of(str.begin(), str.end(), std::isupper);
    }

    bool is_unique(const std::string_view str)
    {
        for (std::size_t i = 0; i < str.length(); ++i)
        {
            for (std::size_t j = i + 1; j < str.length(); ++j)
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
