#include "solutions/day_3/day_3.h"

#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <vector>

#include "ctll.hpp"
#include "ctre.hpp"
#include "fmt/format.h"

#include "utility/io.h"

namespace aoc
{
    static std::string parse_input(const std::filesystem::path& path)
    {
        std::vector<std::string> lines = read_lines(path);
        return std::views::join(lines) | std::ranges::to<std::string>();
    }

    std::string Day3::part_1(const std::filesystem::path& input_root) const
    {
        const std::string program = parse_input(input_root / "day_3.txt");

        int result = 0;
        constexpr ctll::fixed_string pattern = R"(mul\((?<lhs>\d{1,3}),(?<rhs>\d{1,3})\))";
        for (const auto& match : ctre::search_all<pattern>(program))
        {
            int lhs = match.get<"lhs">().to_number();
            int rhs = match.get<"rhs">().to_number();
            result += lhs * rhs;
        }

        return fmt::format("Multiplication results: {}", result);
    }

    std::string Day3::part_2(const std::filesystem::path& input_root) const
    {
        const std::string program = parse_input(input_root / "day_3.txt");

        int result = 0;
        constexpr ctll::fixed_string pattern = R"(do\(\)|don't\(\)|mul\((?<lhs>\d{1,3}),(?<rhs>\d{1,3})\))";
        bool enabled = true;
        for (const auto& match : ctre::search_all<pattern>(program))
        {
            if (match == "do()")
            {
                enabled = true;
            }
            else if (match == "don't()")
            {
                enabled = false;
            }
            else if (enabled)
            {
                int lhs = match.get<"lhs">().to_number();
                int rhs = match.get<"rhs">().to_number();
                result += lhs * rhs;
            }
        }

        return fmt::format("Multiplication results with conditions: {}", result);
    }

} // aoc
