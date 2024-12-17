#ifndef AOC_2024_DAY_18_H
#define AOC_2024_DAY_18_H

#include <filesystem>
#include <string>

#include "utility/day.h"

namespace aoc
{
    class Day18 : public Day
    {
    public:
        Day18() : Day(18) {}

        std::string part_1(const std::filesystem::path& input_root) const override;
        std::string part_2(const std::filesystem::path& input_root) const override;
    };

} // aoc

#endif // !AOC_2024_DAY_18_H
