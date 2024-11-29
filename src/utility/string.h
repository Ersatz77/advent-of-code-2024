#ifndef AOC_UTILITY_STRING_H
#define AOC_UTILITY_STRING_H

#include <string>
#include <vector>

#include "ctre.hpp"

namespace aoc
{
    // Split a string using a single delimiter
    std::vector<std::string> split(const std::string_view str, const std::string_view delim = " ");

    // Split a string using regex
    template<ctll::fixed_string Pattern = " ">
    std::vector<std::string> regex_split(const std::string_view str)
    {
        auto split_results = ctre::split<Pattern>(str);
        std::vector<std::string> results;
        for (const auto& s : split_results)
        {
            results.emplace_back(s);
        }

        return results;
    }

    // Returns true if the whole string is lowercase
    bool is_lower(const std::string_view str);

    // Returns true if the whole string is uppercase
    bool is_upper(const std::string_view str);

    // Returns true if the characters in the string only appear once
    bool is_unique(const std::string_view str);

} // aoc

#endif // !AOC_UTILITY_STRING_H
