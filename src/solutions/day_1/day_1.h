#ifndef AOC_2024_DAY_1_H
#define AOC_2024_DAY_1_H

#include <filesystem>
#include <string>

#include "utility/day.h"

namespace aoc
{
    class Day1 : public Day
    {
    public:
        Day1() : Day(1) {}

        std::string part_1(const std::filesystem::path& input_root) const override;
        std::string part_2(const std::filesystem::path& input_root) const override;
    };

} // aoc

#endif // !AOC_2024_DAY_1_H
