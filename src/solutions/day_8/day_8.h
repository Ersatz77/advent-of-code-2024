#ifndef AOC_2024_DAY_8_H
#define AOC_2024_DAY_8_H

#include <filesystem>
#include <string>

#include "utility/day.h"

namespace aoc
{
    class Day8 : public Day
    {
    public:
        Day8() : Day(8) {}

        std::string part_1(const std::filesystem::path& input_root) const override;
        std::string part_2(const std::filesystem::path& input_root) const override;
    };

} // aoc

#endif // !AOC_2024_DAY_8_H
