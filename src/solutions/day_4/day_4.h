#ifndef AOC_2024_DAY_4_H
#define AOC_2024_DAY_4_H

#include <filesystem>
#include <string>

#include "utility/day.h"

namespace aoc
{
    class Day4 : public Day
    {
    public:
        Day4() : Day(4) {}

        std::string part_1(const std::filesystem::path& input_root) const override;
        std::string part_2(const std::filesystem::path& input_root) const override;
    };

} // aoc

#endif // !AOC_2024_DAY_4_H
