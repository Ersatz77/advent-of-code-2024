#ifndef AOC_2024_DAY_16_H
#define AOC_2024_DAY_16_H

#include <filesystem>
#include <string>

#include "utility/day.h"

namespace aoc
{
    class Day16 : public Day
    {
    public:
        Day16() : Day(16) {}

        std::string part_1(const std::filesystem::path& input_root) const override;
        std::string part_2(const std::filesystem::path& input_root) const override;
    };

} // aoc

#endif // !AOC_2024_DAY_16_H
