#include "solutions/day_12/day_12.h"

#include <cstddef>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/vec.h"

namespace aoc
{
    static std::unordered_map<Point, char> parse_input(const std::filesystem::path& path)
    {
        std::vector<std::string> lines = read_lines(path);

        std::unordered_map<Point, char> garden;
        for (std::size_t y = 0; y < lines.size(); ++y)
        {
            for (std::size_t x = 0; x < lines.front().length(); ++x)
            {
                garden[make_point(x, y)] = lines[y][x];
            }
        }

        return { garden };
    }

    static bool has_plot_type_at(const std::unordered_map<Point, char>& garden, const Point& pos, const char type)
    {
        const auto it = garden.find(pos);
        if (it != garden.end())
        {
            return it->second == type;
        }

        return false;
    }

    static std::pair<int, int> flood_region(const std::unordered_map<Point, char>& garden, std::unordered_set<Point>& visited, const Point& current, const char type, const bool discounted = false)
    {
        // Mark this plot as visited
        visited.insert(current);

        // Check if the neighboring plots have the same type
        bool has_up = has_plot_type_at(garden, current + Point(0, -1), type);
        bool has_down = has_plot_type_at(garden, current + Point(0, 1), type);
        bool has_left = has_plot_type_at(garden, current + Point(-1, 0), type);
        bool has_right = has_plot_type_at(garden, current + Point(1, 0), type);
        bool has_up_left = has_plot_type_at(garden, current + Point(-1, -1), type);
        bool has_up_right = has_plot_type_at(garden, current + Point(1, -1), type);
        bool has_down_left = has_plot_type_at(garden, current + Point(-1, 1), type);
        bool has_down_right = has_plot_type_at(garden, current + Point(1, 1), type);

        // Calculate perimeter
        int perimeter = 0;
        if (discounted)
        {
            if (!has_up && !has_right) { ++perimeter; }
            if (!has_right && !has_down) { ++perimeter; }
            if (!has_down && !has_left) { ++perimeter; }
            if (!has_left && !has_up) { ++perimeter; }

            if (!has_up_left && has_up && has_left) { ++perimeter; }
            if (!has_up_right && has_up && has_right) { ++perimeter; }
            if (!has_down_left && has_down && has_left) { ++perimeter; }
            if (!has_down_right && has_down && has_right) { ++perimeter; }
        }
        else
        {
            if (!has_up) { ++perimeter; }
            if (!has_down) { ++perimeter; }
            if (!has_left) { ++perimeter; }
            if (!has_right) { ++perimeter; }
        }

        // Flood the next plots in this region
        int area = 1;
        for (const Point& next : current.adjacent_cardinal())
        {
            if (has_plot_type_at(garden, next, type) && !visited.contains(next))
            {
                auto res = flood_region(garden, visited, next, type, discounted);
                area += res.first;
                perimeter += res.second;
            }
        }

        return { area, perimeter };
    }

    std::string Day12::part_1(const std::filesystem::path& input_root) const
    {
        const auto garden = parse_input(input_root / "day_12.txt");

        int cost = 0;
        std::unordered_set<Point> visited;
        for (const auto& [p, type] : garden)
        {
            if (!visited.contains(p))
            {
                auto res = flood_region(garden, visited, p, type);
                cost += res.first * res.second;
            }
        }

        return fmt::format("Total cost to fence all regions: {}", cost);
    }

    std::string Day12::part_2(const std::filesystem::path& input_root) const
    {
        const auto garden = parse_input(input_root / "day_12.txt");

        int cost = 0;
        std::unordered_set<Point> visited;
        for (const auto& [p, type] : garden)
        {
            if (!visited.contains(p))
            {
                auto res = flood_region(garden, visited, p, type, true);
                cost += res.first * res.second;
            }
        }

        return fmt::format("Total discounted cost to fence all regions: {}", cost);
    }

} // aoc
