#include "solutions/day_21/day_21.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <ranges>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "ctre.hpp"
#include "fmt/format.h"

#include "utility/io.h"
#include "utility/utility.h"
#include "utility/vec.h"

namespace aoc
{
    static std::unordered_map<char, Point> keypad_positions = {
        {'A', Point(2, 3)},
        {'0', Point(1, 3)},
        {'1', Point(0, 2)},
        {'2', Point(1, 2)},
        {'3', Point(2, 2)},
        {'4', Point(0, 1)},
        {'5', Point(1, 1)},
        {'6', Point(2, 1)},
        {'7', Point(0, 0)},
        {'8', Point(1, 0)},
        {'9', Point(2, 0)},
        {'a', Point(2, 0)},
        {'^', Point(1, 0)},
        {'<', Point(0, 1)},
        {'v', Point(1, 1)},
        {'>', Point(2, 1)}
    };

    static std::unordered_map<char, Point> keypad_directions = {
        {'^', Point(0, -1)},
        {'>', Point(1, 0)},
        {'v', Point(0, 1)},
        {'<', Point(-1, 0)}
    };

    static std::vector<std::pair<std::string, std::uint64_t>> parse_input(const std::filesystem::path& path)
    {
        std::vector<std::string> lines = read_lines(path);

        std::vector<std::pair<std::string, std::uint64_t>> codes;
        for (const auto& line : lines)
        {
            auto match = ctre::match<R"((?<n>\d+)A)">(line);
            std::uint64_t number = match.get<"n">().to_number();
            codes.emplace_back(line, number);
        }

        return codes;
    }

    static std::vector<std::string> generate_move_sets(const Point& start, const Point& end, const Point& avoid)
    {
        const auto [dx, dy] = end - start;
        const std::size_t abs_dx = static_cast<std::size_t>(std::abs(dx));
        const std::size_t abs_dy = static_cast<std::size_t>(std::abs(dy));

        // Create move set
        std::string moves;

        if (dx < 0) { moves += std::string(abs_dx, '<'); }
        else { moves += std::string(abs_dx, '>'); }

        if (dy < 0) { moves += std::string(abs_dy, '^'); }
        else { moves += std::string(abs_dy, 'v'); }

        // Generate every permutation for the move set
        std::vector<std::string> move_permutations;
        do
        {
            Point current = start;
            bool valid = true;
            for (const char move : moves)
            {
                current += keypad_directions.at(move);
                if (current == avoid)
                {
                    valid = false;
                    break;
                }
            }

            if (valid)
            {
                move_permutations.push_back(moves + "a");
            }

        } while (std::ranges::next_permutation(moves).found);

        return move_permutations;
    }

    static std::uint64_t moves_for_code(
        std::unordered_map<std::tuple<std::string, std::uint64_t, std::uint64_t>, std::uint64_t>& cache,
        const std::string& code,
        const std::uint64_t height = 0,
        const std::uint64_t height_limit = 2)
    {
        const std::tuple<std::string, std::uint64_t, std::uint64_t> key = { code, height, height_limit };
        if (cache.contains(key))
        {
            return cache.at(key);
        }

        Point current = height == 0 ? keypad_positions.at('A') : keypad_positions.at('a');
        const Point avoid = height == 0 ? Point(0, 3) : Point(0, 0);

        std::uint64_t total_moves = 0;
        for (const char c : code)
        {
            const Point next = keypad_positions.at(c);
            const std::vector<std::string> move_sets = generate_move_sets(current, next, avoid);

            if (height == height_limit)
            {
                total_moves += move_sets.front().length();
            }
            else
            {
                std::vector<std::uint64_t> moves = move_sets
                    | std::views::transform([&cache, &height, &height_limit](const auto& move_set) { return moves_for_code(cache, move_set, height + 1, height_limit); })
                    | std::ranges::to<std::vector<std::uint64_t>>();

                total_moves += *std::ranges::min_element(moves);
            }

            current = next;
        }

        cache[key] = total_moves;
        return total_moves;
    }

    std::string Day21::part_1(const std::filesystem::path& input_root) const
    {
        const auto codes = parse_input(input_root / "day_21.txt");

        std::uint64_t complexity = 0;
        std::unordered_map<std::tuple<std::string, std::uint64_t, std::uint64_t>, std::uint64_t> cache;
        for (const auto& [code, number] : codes)
        {
            complexity += number * moves_for_code(cache, code);
        }

        return fmt::format("Sum of the complexities of all door codes: {}", complexity);
    }

    std::string Day21::part_2(const std::filesystem::path& input_root) const
    {
        const auto codes = parse_input(input_root / "day_21.txt");

        std::uint64_t complexity = 0;
        std::unordered_map<std::tuple<std::string, std::uint64_t, std::uint64_t>, std::uint64_t> cache;
        for (const auto& [code, number] : codes)
        {
            complexity += number * moves_for_code(cache, code, 0, 25);
        }

        return fmt::format("Sum of the complexities of all door codes: {}", complexity);
    }

} // aoc
