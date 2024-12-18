#include "solutions/day_18/day_18.h"

#include <cmath>
#include <filesystem>
#include <fstream>
#include <optional>
#include <queue>
#include <ranges>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ctre.hpp"
#include "fmt/format.h"

#include "utility/io.h"
#include "utility/math.h"
#include "utility/vec.h"

namespace aoc
{

    static std::tuple<std::vector<Point>, Point, Point> parse_input(const std::filesystem::path& path)
    {
        std::ifstream file = open_file(path);

        Point min = Point::origin();
        Point max = Point::origin();
        std::vector<Point> will_corrupt;
        for (std::string line; std::getline(file, line); )
        {
            const auto match = ctre::match<R"((?<x>\d+),(?<y>\d+))">(line);
            const double x = match.get<"x">().to_number();
            const double y = match.get<"y">().to_number();

            max.x = std::max(max.x, x);
            max.y = std::max(max.y, y);

            will_corrupt.emplace_back(x, y);
        }

        return { will_corrupt, min, max };
    }

    static std::optional<int> walk_corrupted_memory(
        const std::vector<Point>& will_corrupt,
        const std::size_t max_corruption,
        const Point& min,
        const Point& max,
        const Point& start,
        const Point& end)
    {
        std::unordered_set<Point> corrupted = will_corrupt | std::views::take(max_corruption) | std::ranges::to<std::unordered_set<Point>>();

        using WalkNode = std::pair<int, Point>;

        const auto cmp = [](const WalkNode& left, const WalkNode& right) { return left.first > right.first; };
        std::priority_queue<WalkNode, std::vector<WalkNode>, decltype(cmp)> to_visit;
        std::unordered_set<Point> visited;

        to_visit.emplace(0, start);

        while (!to_visit.empty())
        {
            const auto [steps, current] = to_visit.top();
            to_visit.pop();

            // Return steps if we reached the end
            if (current == end)
            {
                return steps;
            }

            // Skip position if it was already visited
            if (visited.contains(current))
            {
                continue;
            }

            visited.insert(current);

            // Queue next positions
            for (const auto& next : current.adjacent_cardinal())
            {
                if (in_area(min, max, next) && !corrupted.contains(next))
                {
                    to_visit.emplace(steps + 1, next);
                }
            }
        }

        return std::nullopt;
    }

    std::string Day18::part_1(const std::filesystem::path& input_root) const
    {
        const auto [will_corrupt, min, max] = parse_input(input_root / "day_18.txt");

        const int min_steps = *walk_corrupted_memory(will_corrupt, 1024, min, max, min, max);

        return fmt::format("Minimum steps required to reach the exit: {}", min_steps);
    }

    std::string Day18::part_2(const std::filesystem::path& input_root) const
    {
        const auto [will_corrupt, min, max] = parse_input(input_root / "day_18.txt");

        // Binary search to find the first position that blocks the path
        Point blocked_path = Point::origin();
        std::size_t low = 1024;
        std::size_t high = will_corrupt.size();
        while ((high - low) > 1)
        {
            std::size_t mid = (high + low) / 2;
            if (walk_corrupted_memory(will_corrupt, mid, min, max, min, max))
            {
                blocked_path = will_corrupt[mid];
                low = mid;
            }
            else
            {
                high = mid;
            }
        }

        return fmt::format("First byte that blocked the exit: {},{}", blocked_path.x, blocked_path.y);
    }

} // aoc
