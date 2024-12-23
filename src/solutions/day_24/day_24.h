#ifndef AOC_2024_DAY_24_H
#define AOC_2024_DAY_24_H

#include <filesystem>
#include <string>

#include "utility/day.h"

namespace aoc
{
    class Day24 : public Day
    {
    public:
        Day24() : Day(24) {}

        std::string part_1(const std::filesystem::path& input_root) const override;
        std::string part_2(const std::filesystem::path& input_root) const override;
    };

} // aoc

#endif // !AOC_2024_DAY_24_H
