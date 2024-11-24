#ifndef AOC_UTILITY_STRING_H
#define AOC_UTILITY_STRING_H

#include <string>
#include <vector>

namespace aoc
{
    // Split a string using a single delimiter
    std::vector<std::string> split(const std::string& str, const char delim = ' ');

    // Split a string using regex
    std::vector<std::string> regex_split(const std::string& str, const std::string& pattern);

    // Returns true if the whole string is lowercase
    bool is_lower(const std::string& str);

    // Returns true if the whole string is uppercase
    bool is_upper(const std::string& str);

    // Returns true if the characters in the string only appear once
    bool is_unique(const std::string& str);

} // aoc

#endif // !AOC_UTILITY_STRING_H
