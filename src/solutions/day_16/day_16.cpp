#include "solutions/day_16/day_16.h"

#include <array>
#include <cstddef>
#include <filesystem>
#include <limits>
#include <optional>
#include <queue>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "fmt/format.h"

#include "utility/io.h"
#include "utility/utility.h"
#include "utility/vec.h"

namespace aoc
{
    struct ReindeerDirection
    {
        static constexpr Vec2<int> north = { 0, -1 };
        static constexpr Vec2<int> east = { 1,  0 };
        static constexpr Vec2<int> south = { 0,  1 };
        static constexpr Vec2<int> west = { -1,  0 };

        static Vec2<int> turn_right(const Vec2<int>& dir)
        {
            if (dir == north) { return east; }
            else if (dir == east) { return south; }
            else if (dir == south) { return west; }
            else if (dir == west) { return north; }

            throw std::invalid_argument("Invalid direction");
        }

        static Vec2<int> turn_left(const Vec2<int>& dir)
        {
            if (dir == north) { return west; }
            else if (dir == west) { return south; }
            else if (dir == south) { return east; }
            else if (dir == east) { return north; }

            throw std::invalid_argument("Invalid direction");
        }
    };

    static std::tuple<std::vector<std::string>, Vec2<int>, Vec2<int>> parse_input(const std::filesystem::path& path)
    {
        std::vector<std::string> maze = read_lines(path);

        // Find start and end
        Vec2<int> start = Vec2<int>::origin();
        Vec2<int> end = Vec2<int>::origin();
        for (std::size_t y = 0; y < maze.size(); ++y)
        {
            for (std::size_t x = 0; x < maze.front().length(); ++x)
            {
                switch (maze[y][x])
                {
                    case 'S':
                        start = make_vec2<int>(x, y);
                        break;
                    case 'E':
                        end = make_vec2<int>(x, y);
                        break;
                    default:
                        break;
                }
            }
        }

        return { maze, start, end };
    }

    static int shortest_path_score(const std::vector<std::string>& maze, const Vec2<int>& start, const Vec2<int>& end)
    {
        using Position = Vec2<int>;
        using Direction = Vec2<int>;
        using WalkNode = std::tuple<int, Position, Direction>;

        const auto cmp = [](const WalkNode& left, const WalkNode& right) { return std::get<0>(left) > std::get<0>(right); };
        std::priority_queue<WalkNode, std::vector<WalkNode>, decltype(cmp)> to_visit;
        std::unordered_set<std::pair<Position, Direction>> visited;

        to_visit.emplace(0, start, ReindeerDirection::east);

        while (!to_visit.empty())
        {
            const auto [score, current_pos, current_dir] = to_visit.top();
            to_visit.pop();

            // Return score if we reached the end
            if (current_pos == end)
            {
                return score;
            }

            // Skip node if it has been visited
            std::pair<Position, Direction> key = { current_pos, current_dir };
            if (visited.contains(key))
            {
                continue;
            }

            visited.insert(key);

            // Push next nodes
            const std::array<std::pair<int, Direction>, 3> next = {
                { {1, current_dir}, {1001, ReindeerDirection::turn_left(current_dir)}, {1001, ReindeerDirection::turn_right(current_dir)} }
            };
            for (const auto& [added_score, next_dir] : next)
            {
                Position next_pos = current_pos + next_dir;
                if (maze[next_pos.y][next_pos.x] != '#')
                {
                    to_visit.emplace(score + added_score, next_pos, next_dir);
                }
            }
        }

        return -1;
    }

    static int positions_on_shortest_paths(const std::vector<std::string>& maze, const Vec2<int>& start, const Vec2<int>& end, const int target_score)
    {
        using Position = Vec2<int>;
        using Direction = Vec2<int>;
        using WalkNode = std::tuple<int, Position, Direction, std::optional<Position>, std::optional<Direction>>;

        std::unordered_map<std::pair<Position, Direction>, int> best_scores;
        std::unordered_map<std::pair<Position, Direction>, std::unordered_set<std::pair<Position, Direction>>> paths;

        const auto cmp = [](const WalkNode& left, const WalkNode& right) { return std::get<0>(left) > std::get<0>(right); };
        std::priority_queue<WalkNode, std::vector<WalkNode>, decltype(cmp)> to_visit;

        to_visit.emplace(0, start, ReindeerDirection::east, std::nullopt, std::nullopt);

        while (!to_visit.empty())
        {
            const auto [score, current_pos, current_dir, previous_pos, previous_dir] = to_visit.top();
            to_visit.pop();

            // We can't find any more routes
            if (score > target_score)
            {
                break;
            }

            // Check if we can record a new good route
            std::pair<Position, Direction> key = { current_pos, current_dir };
            if (best_scores.contains(key))
            {
                if (best_scores.at(key) == score && previous_pos && previous_dir)
                {
                    paths[key].emplace(*previous_pos, *previous_dir);
                }

                continue;
            }

            // Found a new best score
            best_scores[key] = score;
            if (previous_pos && previous_dir)
            {
                paths[key].emplace(*previous_pos, *previous_dir);
            }

            // Push next nodes
            const std::array<std::pair<int, Direction>, 3> next = {
                { {1, current_dir}, {1001, ReindeerDirection::turn_left(current_dir)}, {1001, ReindeerDirection::turn_right(current_dir)} }
            };
            for (const auto& [added_score, next_dir] : next)
            {
                Position next_pos = current_pos + next_dir;
                if (maze[next_pos.y][next_pos.x] != '#')
                {
                    to_visit.emplace(score + added_score, next_pos, next_dir, current_pos, current_dir);
                }
            }
        }

        // Backtrack from the end and record our positions and routes
        std::unordered_set<std::pair<Position, Direction>> routes;
        std::unordered_set<Position> positions;
        constexpr std::array<Direction, 4> directions = {
            { ReindeerDirection::north, ReindeerDirection::east, ReindeerDirection::north, ReindeerDirection::west }
        };
        for (const auto& dir : directions)
        {
            std::queue<std::pair<Position, Direction>> to_visit_backwards;
            to_visit_backwards.emplace(end, dir);
            while (!to_visit_backwards.empty())
            {
                const auto current = to_visit_backwards.front();
                to_visit_backwards.pop();

                if (!routes.contains(current))
                {
                    routes.insert(current);
                    positions.insert(current.first);
                    if (paths.contains(current))
                    {
                        to_visit_backwards.push_range(paths.at(current));
                    }
                }
            }
        }

        return static_cast<int>(positions.size());
    }

    std::string Day16::part_1(const std::filesystem::path& input_root) const
    {
        const auto [maze, start, end] = parse_input(input_root / "day_16.txt");

        const int score = shortest_path_score(maze, start, end);

        return fmt::format("Lowest score a reindeer could get: {}", score);
    }

    std::string Day16::part_2(const std::filesystem::path& input_root) const
    {
        const auto [maze, start, end] = parse_input(input_root / "day_16.txt");

        const int score = shortest_path_score(maze, start, end);
        const int on_path = positions_on_shortest_paths(maze, start, end, score);

        return fmt::format("Tiles on a best path through the maze: {}", on_path);
    }

} // aoc
