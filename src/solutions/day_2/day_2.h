#ifndef AOC_2024_DAY_2_H
#define AOC_2024_DAY_2_H

#include <filesystem>
#include <string>

#include "utility/day.h"

namespace aoc
{
    class Day2 : public Day
    {
    public:
        Day2() : Day(2) {}

        std::string part_1(const std::filesystem::path& input_root) const override;
        std::string part_2(const std::filesystem::path& input_root) const override;
    };

} // aoc

#endif // !AOC_2024_DAY_2_H
