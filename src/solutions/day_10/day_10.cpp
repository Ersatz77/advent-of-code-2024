#include "solutions/day_10/day_10.h"

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/vec.h"

namespace aoc
{
    static std::unordered_map<Point, int> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        std::unordered_map<Point, int> map;
        std::size_t y = 0;
        for (std::string line; std::getline(file, line); )
        {
            for (std::size_t x = 0; x < line.length(); ++x)
            {
                int height = static_cast<int>(line[x] - '0');
                map[make_point(x, y)] = height;
            }

            ++y;
        }

        return map;
    }

    static std::pair<std::size_t, std::uint64_t> walk_trails(const std::unordered_map<Point, int>& map, const Point& trailhead)
    {
        std::queue<Point> to_visit({ trailhead });
        std::unordered_set<Point> unique_trail_ends;
        std::uint64_t trail_ends = 0;
        while (!to_visit.empty())
        {
            const Point current = to_visit.front();
            to_visit.pop();

            // Add to the score if we've reached the highest point
            if (map.at(current) == 9)
            {
                unique_trail_ends.insert(current);
                ++trail_ends;
                continue;
            }

            // Get the next positions
            const int current_height = map.at(current);
            for (const Point& next : current.adjacent_cardinal())
            {
                // Skip next position if it's outside of the map
                if (!map.contains(next))
                {
                    continue;
                }

                // Add next position if it's `1` higher than the current position
                const int next_height = map.at(next);
                if (next_height - current_height == 1)
                {
                    to_visit.push(next);
                }
            }
        }

        return { unique_trail_ends.size(), trail_ends };
    }

    std::string Day10::part_1(const std::filesystem::path& input_root) const
    {
        const auto map = parse_input(input_root / "day_10.txt");

        std::uint64_t score = 0;
        for (const auto& [pos, height] : map)
        {
            if (height == 0)
            {
                score += walk_trails(map, pos).first;
            }
        }

        return fmt::format("Sum of trailhead scores: {}", score);
    }

    std::string Day10::part_2(const std::filesystem::path& input_root) const
    {
        const auto map = parse_input(input_root / "day_10.txt");

        std::uint64_t rating = 0;
        for (const auto& [pos, height] : map)
        {
            if (height == 0)
            {
                rating += walk_trails(map, pos).second;
            }
        }

        return fmt::format("Sum of trailhead ratings: {}", rating);
    }

} // aoc
