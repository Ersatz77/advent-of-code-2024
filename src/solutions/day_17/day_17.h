#ifndef AOC_2024_DAY_17_H
#define AOC_2024_DAY_17_H

#include <filesystem>
#include <string>

#include "utility/day.h"

namespace aoc
{
    class Day17 : public Day
    {
    public:
        Day17() : Day(17) {}

        std::string part_1(const std::filesystem::path& input_root) const override;
        std::string part_2(const std::filesystem::path& input_root) const override;
    };

} // aoc

#endif // !AOC_2024_DAY_17_H
