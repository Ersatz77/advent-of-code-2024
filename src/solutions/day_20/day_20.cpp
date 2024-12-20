#include "solutions/day_20/day_20.h"

#include <algorithm>
#include <cstddef>
#include <filesystem>
#include <queue>
#include <ranges>
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
    static std::tuple<std::unordered_set<Point>, Point, Point> parse_input(const std::filesystem::path& path)
    {
        std::vector<std::string> maze = read_lines(path);

        std::unordered_set<Point> walls;
        Point start = Point::origin();
        Point end = Point::origin();
        for (std::size_t y = 0; y < maze.size(); ++y)
        {
            for (std::size_t x = 0; x < maze.front().length(); ++x)
            {
                switch (maze[y][x])
                {
                    case '#':
                        walls.insert(make_point(x, y));
                        break;
                    case 'S':
                        start = make_point(x, y);
                        break;
                    case 'E':
                        end = make_point(x, y);
                        break;
                    default:
                        break;
                }
            }
        }

        return { walls, start, end };
    }

    static std::unordered_map<Point, int> walk_maze(const std::unordered_set<Point>& walls, const Point& start, const Point& end)
    {
        // BFS to find the distance for each position
        std::queue<std::pair<Point, int>> to_visit({ {start, 0} });
        std::unordered_map<Point, int> visited;

        while (!to_visit.empty())
        {
            const auto [current, distance] = to_visit.front();
            to_visit.pop();

            // Skip position if it has already been visited
            if (visited.contains(current))
            {
                continue;
            }

            visited[current] = distance;

            // Skip position if we reached the end
            if (current == end)
            {
                continue;
            }

            // Queue next positions
            for (const auto& next : current.adjacent_cardinal())
            {
                if (!walls.contains(next))
                {
                    to_visit.emplace(next, distance + 1);
                }
            }
        }

        return visited;
    }

    std::string Day20::part_1(const std::filesystem::path& input_root) const
    {
        const auto [walls, start, end] = parse_input(input_root / "day_20.txt");

        // Walk the maze to get the distances for each position
        const auto visited = walk_maze(walls, start, end);

        // Walk all visited positions and calculate the time saved by taking a shortcut
        constexpr int max_cheat_distance = 2;
        constexpr int min_time_saved = 100;
        int saved_time = 0;
        for (const auto& [current, distance] : visited)
        {
            for (const auto& delta : Point::adjacent_cardinal_deltas())
            {
                Point skip_to = current + delta + delta;
                if (visited.contains(skip_to))
                {
                    int time_saved = visited.at(skip_to) - distance - max_cheat_distance;
                    if (time_saved >= min_time_saved)
                    {
                        ++saved_time;
                    }
                }
            }
        }

        return fmt::format("Shortcuts that saved at least 100 picoseconds: {}", saved_time);
    }

    std::string Day20::part_2(const std::filesystem::path& input_root) const
    {
        const auto [walls, start, end] = parse_input(input_root / "day_20.txt");

        // Walk the maze to get the distances for each position
        // Also turn the map into a vector so iterating over it is quicker
        std::vector<std::pair<Point, int>> visited = walk_maze(walls, start, end)
            | std::views::transform([](const auto& p) { return p; })
            | std::ranges::to<std::vector<std::pair<Point, int>>>();

        // Sort the vector by distance so we iterate over it correctly
        std::ranges::sort(visited, [](const auto& left, const auto& right) { return left.second < right.second; });

        // Walk all visited positions and calculate the time saved by taking a shortcut
        constexpr int max_cheat_distance = 20;
        constexpr int min_time_saved = 100;
        int saved_time = 0;
        for (std::size_t i = 0; i < visited.size(); ++i)
        {
            const auto& [current, distance] = visited[i];
            for (std::size_t j = i + 1; j < visited.size(); ++j)
            {
                const auto& [skip_to, skip_to_distance] = visited[j];
                double cheat_distance = manhattan_distance(current, skip_to);
                if (cheat_distance <= max_cheat_distance && skip_to_distance - distance - cheat_distance >= min_time_saved)
                {
                    ++saved_time;
                }
            }
        }

        return fmt::format("Shortcuts that saved at least 100 picoseconds: {}", saved_time);
    }

} // aoc
