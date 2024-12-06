#include "solutions/day_6/day_6.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/math.h"
#include "utility/utility.h"
#include "utility/vec.h"

namespace aoc
{
    static std::tuple<Point, std::unordered_set<Point>, std::pair<Point, Point>> parse_input(const std::filesystem::path& path)
    {
        std::vector<std::string> lines = read_lines(path);

        Point guard;
        std::unordered_set<Point> obstacles;
        Point min = Point::origin();
        Point max = make_point(lines.front().length() - 1, lines.size() - 1);
        for (std::size_t y = 0; y < lines.size(); ++y)
        {
            for (std::size_t x = 0; x < lines.front().length(); ++x)
            {
                switch (lines[y][x])
                {
                    case '#':
                        obstacles.insert(make_point(x, y));
                        break;
                    case '^':
                        guard = make_point(x, y);
                        break;
                    default:
                        break;
                }
            }
        }

        return { guard, obstacles, { min, max } };
    }

    static std::pair<std::unordered_set<Point>, bool> walk_lab(
        const Point& guard_start,
        const std::unordered_set<Point>& obstacles,
        const std::pair<Point, Point>& bounds)
    {
        using GuardState = std::pair<Point, std::size_t>;

        GuardState guard = { guard_start, 0 };
        std::unordered_set<GuardState> states;
        std::unordered_set<Point> visited;
        while (in_area(bounds.first, bounds.second, guard.first) && !states.contains(guard))
        {
            states.insert(guard);
            visited.insert(guard.first);

            constexpr std::array<Point, 4> directions = { {{0, -1}, {1, 0}, {0, 1}, {-1, 0}} };
            if (obstacles.contains(guard.first + directions[guard.second]))
            {
                guard.second = (guard.second + 1) % 4;
            }
            else
            {
                guard.first += directions[guard.second];
            }
        }

        return { visited, states.contains(guard) };
    }

    std::string Day6::part_1(const std::filesystem::path& input_root) const
    {
        const auto [guard, obstacles, bounds] = parse_input(input_root / "day_6.txt");
        const auto [path, _] = walk_lab(guard, obstacles, bounds);

        return fmt::format("Positions the guard visited: {}", path.size());
    }

    std::string Day6::part_2(const std::filesystem::path& input_root) const
    {
        const auto [guard, obstacles, bounds] = parse_input(input_root / "day_6.txt");
        const auto [path, _] = walk_lab(guard, obstacles, bounds);

        const std::size_t loops = std::ranges::count_if(path,
            [&guard, &obstacles, &bounds](const Point& p) {
                std::unordered_set<Point> new_obstacles = obstacles;
                new_obstacles.insert(p);
                return walk_lab(guard, new_obstacles, bounds).second;
            }
        );

        return fmt::format("Obstacle placements that causes the guard to loop: {}", loops);
    }

} // aoc
