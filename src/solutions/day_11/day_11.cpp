#include "solutions/day_11/day_11.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <unordered_map>

#include "fmt/format.h"

#include "utility/io.h"

namespace aoc
{
    static std::unordered_map<std::uint64_t, std::uint64_t> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::unordered_map<std::uint64_t, std::uint64_t> stones;
        for (const std::uint64_t stone : std::views::istream<std::uint64_t>(file))
        {
            ++stones[stone];
        }

        return stones;
    }

    static void simulate_stones(std::unordered_map<std::uint64_t, std::uint64_t>& stones, const std::uint64_t blinks)
    {
        for (std::uint64_t i = 0; i < blinks; ++i)
        {
            std::unordered_map<std::uint64_t, std::uint64_t> new_stones;
            for (const auto& [number, count] : stones)
            {
                if (number == 0)
                {
                    new_stones[1] += count;
                }
                else if (std::string s = std::to_string(number); s.length() % 2 == 0)
                {
                    std::uint64_t left = std::stoull(s.substr(0, s.length() / 2));
                    std::uint64_t right = std::stoull(s.substr(s.length() / 2, s.length() / 2));

                    new_stones[left] += count;
                    new_stones[right] += count;
                }
                else
                {
                    new_stones[number * 2024] += count;
                }
            }

            stones = new_stones;
        }
    }

    std::string Day11::part_1(const std::filesystem::path& input_root) const
    {
        auto stones = parse_input(input_root / "day_11.txt");

        simulate_stones(stones, 25);
        std::uint64_t total = *std::ranges::fold_left_first(std::views::values(stones), std::plus<std::uint64_t>());

        return fmt::format("Total number of stones after 25 blinks: {}", total);
    }

    std::string Day11::part_2(const std::filesystem::path& input_root) const
    {
        auto stones = parse_input(input_root / "day_11.txt");

        simulate_stones(stones, 75);
        std::uint64_t total = *std::ranges::fold_left_first(std::views::values(stones), std::plus<std::uint64_t>());

        return fmt::format("Total number of stones after 75 blinks: {}", total);
    }

} // aoc
