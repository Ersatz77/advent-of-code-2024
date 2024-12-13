#ifndef AOC_2024_DAY_14_H
#define AOC_2024_DAY_14_H

#include <filesystem>
#include <string>

#include "utility/day.h"

namespace aoc
{
    class Day14 : public Day
    {
    public:
        Day14() : Day(14) {}

        std::string part_1(const std::filesystem::path& input_root) const override;
        std::string part_2(const std::filesystem::path& input_root) const override;
    };

} // aoc

#endif // !AOC_2024_DAY_14_H
