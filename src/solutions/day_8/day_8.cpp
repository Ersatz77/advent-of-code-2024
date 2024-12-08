#include "solutions/day_8/day_8.h"

#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/math.h"
#include "utility/vec.h"

namespace aoc
{
    static std::tuple<std::unordered_map<char, std::vector<Point>>, std::pair<Point, Point>> parse_input(const std::filesystem::path& path)
    {
        std::vector<std::string> lines = read_lines(path);

        Point min = Point::origin();
        Point max = make_point(lines.front().length() - 1, lines.size() - 1);

        std::unordered_map<char, std::vector<Point>> antennas;
        for (std::size_t y = 0; y < lines.size(); ++y)
        {
            for (std::size_t x = 0; x < lines.front().length(); ++x)
            {
                if (lines[y][x] != '.')
                {
                    antennas[lines[y][x]].push_back(make_point(x, y));
                }
            }
        }

        return { antennas, {min, max} };
    }
    std::string Day8::part_1(const std::filesystem::path& input_root) const
    {
        const auto [antennas, bounds] = parse_input(input_root / "day_8.txt");

        std::unordered_set<Point> antinodes;
        for (const auto& [_, group] : antennas)
        {
            for (std::size_t i = 0; i < group.size(); ++i)
            {
                for (std::size_t j = i + 1; j < group.size(); ++j)
                {
                    Point a = group[i];
                    Point b = group[j];
                    if (a > b)
                    {
                        std::swap(a, b);
                    }

                    Point slope = b - a;
                    Point anti_a = a - slope;
                    Point anti_b = b + slope;

                    if (in_area(bounds.first, bounds.second, anti_a))
                    {
                        antinodes.insert(anti_a);
                    }

                    if (in_area(bounds.first, bounds.second, anti_b))
                    {
                        antinodes.insert(anti_b);
                    }
                }
            }
        }

        return fmt::format("Unique antinodes within the map: {}", antinodes.size());
    }

    std::string Day8::part_2(const std::filesystem::path& input_root) const
    {
        const auto [antennas, bounds] = parse_input(input_root / "day_8.txt");

        std::unordered_set<Point> antinodes;
        for (const auto& [_, group] : antennas)
        {
            for (std::size_t i = 0; i < group.size(); ++i)
            {
                for (std::size_t j = i + 1; j < group.size(); ++j)
                {
                    Point a = group[i];
                    Point b = group[j];

                    if (a > b)
                    {
                        std::swap(a, b);
                    }

                    antinodes.insert(a);
                    antinodes.insert(b);

                    Point slope = b - a;
                    Point anti_a = a - slope;
                    Point anti_b = b + slope;

                    while (in_area(bounds.first, bounds.second, anti_a))
                    {
                        antinodes.insert(anti_a);
                        anti_a -= slope;
                    }

                    while (in_area(bounds.first, bounds.second, anti_b))
                    {
                        antinodes.insert(anti_b);
                        anti_b += slope;
                    }
                }
            }
        }

        return fmt::format("Unique antinodes within the map: {}", antinodes.size());
    }

} // aoc
