#ifndef AOC_2024_DAY_22_H
#define AOC_2024_DAY_22_H

#include <filesystem>
#include <string>

#include "utility/day.h"

namespace aoc
{
    class Day22 : public Day
    {
    public:
        Day22() : Day(22) {}

        std::string part_1(const std::filesystem::path& input_root) const override;
        std::string part_2(const std::filesystem::path& input_root) const override;
    };

} // aoc

#endif // !AOC_2024_DAY_22_H
