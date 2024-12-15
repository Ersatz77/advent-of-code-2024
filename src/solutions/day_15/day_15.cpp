#include "solutions/day_15/day_15.h"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "fmt/format.h"

#include "solutions/day_15/warehouse.h"
#include "utility/io.h"
#include "utility/vec.h"

namespace aoc
{


    static std::pair<Warehouse, std::vector<Point>> parse_input(const std::filesystem::path& path, const bool double_width = false)
    {
        std::ifstream file = open_file(path);

        std::unordered_set<Point> walls;
        std::vector<WarehouseBox> boxes;
        Point robot = Point::origin();

        // Parse warehouse
        std::size_t y = 0;
        for (std::string line; std::getline(file, line) && !line.empty(); )
        {
            // Update the line if it needs to be doubled
            if (double_width)
            {
                std::string new_line;
                for (const char c : line)
                {
                    switch (c)
                    {
                        case '.':
                            new_line += "..";
                            break;
                        case '#':
                            new_line += "##";
                            break;
                        case 'O':
                            new_line += "[]";
                            break;
                        case '@':
                            new_line += "@.";
                            break;
                        default:
                            break;
                    }
                }

                line = new_line;
            }

            for (std::size_t x = 0; x < line.length(); ++x)
            {
                switch (line[x])
                {
                    case '#':
                        walls.insert(make_point(x, y));
                        break;
                    case 'O':
                        boxes.emplace_back(make_point(x, y));
                        break;
                    case '[':
                        boxes.emplace_back(make_point(x, y), make_point(x + 1, y));
                        ++x;
                        break;
                    case '@':
                        robot = make_point(x, y);
                        break;
                    default:
                        break;
                }
            }

            ++y;
        }

        // Parse robot moves
        std::vector<Point> robot_moves;
        for (const char c : std::views::istream<char>(file))
        {
            switch (c)
            {
                case '^':
                    robot_moves.push_back(RobotMoveDirection::up);
                    break;
                case 'v':
                    robot_moves.push_back(RobotMoveDirection::down);
                    break;
                case '<':
                    robot_moves.push_back(RobotMoveDirection::left);
                    break;
                case '>':
                    robot_moves.push_back(RobotMoveDirection::right);
                    break;
                default:
                    break;
            }
        }

        return { { walls, boxes, robot }, robot_moves };
    }

    std::string Day15::part_1(const std::filesystem::path& input_root) const
    {
        auto [warehouse, moves] = parse_input(input_root / "day_15.txt");

        for (const auto& move : moves)
        {
            warehouse.move_robot(move);
        }

        return fmt::format("Sum of all boxes' GPS coords: {}", warehouse.gps_sum());
    }

    std::string Day15::part_2(const std::filesystem::path& input_root) const
    {
        auto [warehouse, moves] = parse_input(input_root / "day_15.txt", true);

        for (const auto& move : moves)
        {
            warehouse.move_robot(move);
        }

        return fmt::format("Sum of all boxes' GPS coords: {}", warehouse.gps_sum());
    }

} // aoc
